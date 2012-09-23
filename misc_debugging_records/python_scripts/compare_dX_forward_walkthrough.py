#============================================================
# Read in potentially useful python modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime
#============================================================
# Read in the raw data
#============================================================
savedirBase = eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
#'/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/2012/Sep/Sep_21_2012/v1/'
savedirBase += '/'

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_A_*.txt'):
        filelist.append(file)
file1a = savedirBase+str(filelist[0])

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_B_*.txt'):
        filelist.append(file)
file1b = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_G_*.txt'):
        filelist.append(file)
fileHelenaG = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_C_*.txt'):
        filelist.append(file)
fileHelenaC = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_D_*.txt'):
        filelist.append(file)
fileHelenaD = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_E_*.txt'):
        filelist.append(file)
fileHelenaE = savedirBase+(str(filelist[0]))

file2a = '/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/Uncategorized_Text_Files/A_matrix_vals_from_Peter_CDEGs.txt'
file2b = '/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/Uncategorized_Text_Files/B_matrix_vals_from_Peter_CDEGs.txt'
filePeterG = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/g_values.txt'
filePeterC = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/c_values.txt'
filePeterD = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/d_values.txt'
filePeterE = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/e_values.txt'


HA_benchmark = numpy.loadtxt(file1a)
HB_benchmark = numpy.loadtxt(file1b)
HC = numpy.loadtxt(fileHelenaC,skiprows=1)[:,1:]
HD = numpy.loadtxt(fileHelenaD,skiprows=1)[:,1:]
HE = numpy.loadtxt(fileHelenaE,skiprows=1)[:,1:]
HG = numpy.loadtxt(fileHelenaG,skiprows=1)[:,1:]

PA_benchmark = numpy.loadtxt(file2a,skiprows=1)
PB_benchmark = numpy.loadtxt(file2b)
PC = numpy.loadtxt(filePeterC)
PD = numpy.loadtxt(filePeterD)
PE = numpy.loadtxt(filePeterE)
PG = numpy.loadtxt(filePeterG,skiprows=2)

HG[-1] = PG[-1]
HC[-1] = PC[-1]
HD[-1] = PD[-1]
HE[-1] = PE[-1]
#============================================================
# Declare constants to help with the calculations
# and plotting
#============================================================
Color1 = cm.spectral(50)
Color2 = cm.spectral(0)
Color3 = cm.Dark2(110)
Color4 = cm.Dark2(35)

jMax = HG.shape[0]
iMax = 4

np.set_printoptions(precision=3)

plt.close("all")
plt.clf()
matplotlib.rc('xtick', labelsize=10) 
matplotlib.rc('ytick', labelsize=10) 
plt.subplots_adjust(wspace=0.3,hspace=0.3)
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

#============================================================
# Format the data for plotting and calculating
#============================================================
HA_benchmark = numpy.reshape(HA_benchmark,[jMax,iMax])
HB_benchmark = numpy.reshape(HB_benchmark,[jMax,iMax,iMax])
HG = numpy.reshape(HG,[jMax,iMax])
HC = numpy.reshape(HC,[jMax,iMax,iMax])
HD = numpy.reshape(HD,[jMax,iMax,iMax])
HE = numpy.reshape(HE,[jMax,iMax,iMax])

PA_benchmark = numpy.reshape(PA_benchmark,[jMax,iMax])
PB_benchmark = numpy.reshape(PB_benchmark,[jMax,iMax,iMax])
PG = numpy.reshape(PG,[jMax,iMax])
PC = numpy.reshape(PC,[jMax,iMax,iMax])
PD = numpy.reshape(PD,[jMax,iMax,iMax])
PE = numpy.reshape(PE,[jMax,iMax,iMax])

#============================================================
# Start walking through the dX calculations,
# from the inside out.
#============================================================
HS = numpy.zeros((jMax,iMax,iMax))
HSum = numpy.zeros((jMax,iMax))
HA = numpy.zeros((jMax,iMax))
HB = numpy.zeros((jMax,iMax,iMax))

PS = numpy.zeros((jMax,iMax,iMax))
PSum = numpy.zeros((jMax,iMax))
PA = numpy.zeros((jMax,iMax))
PB = numpy.zeros((jMax,iMax,iMax))

for j in range(jMax):
    if j==0:
        HS[j] = HD[j]
        HSum[j] = HG[j]

        PS[j] = PD[j].T
        PSum[j] = PG[j]
    else:
        HS[j] = dot(HC[j],HB[j-1]) + HD[j]
        HSum[j] = dot(HC[j],HA[j-1]) + HG[j]

        PS[j] = dot(PC[j].T,PB[j-1]) + PD[j].T
        PSum[j] = dot(PC[j].T,PA[j-1]) + PG[j]

    HA[j] = -1.0 * dot( inv(HS[j]) , HSum[j]) 
    HB[j] = -1.0 * dot( inv(HS[j]) , HE[j])

    PA[j] = -1.0 * dot( inv(PS[j]) , PSum[j])
    PB[j] = -1.0 * dot( inv(PS[j]) , PE[j].T)

    #sys.exit(0)

#============================================================
# Plot/compare the results
#============================================================
File1 = savedirBase.split('Desktop')[-1]
File2 = filePeterG.split('Desktop')[-1]
date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+File1+"\n"+File2

for i in range(iMax):
    print(i)
    
    plt.figure(1)
    plt.subplots_adjust(wspace=0.3,hspace=0.3)
    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
    plt.suptitle('PA vs. HA')
    plt.subplot(4,1,i+1)
    plot(PA[:,i]/HA[:,i] ,'-o',color=Color2,linewidth=2,label='PA/HA')

    plt.figure(2)
    plt.subplots_adjust(wspace=0.3,hspace=0.3)
    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
    plt.suptitle('PG vs. HG')
    plt.subplot(4,1,i+1)
    plot(PG[:,i]/HG[:,i] ,'-o',color=Color2,linewidth=2,label='PG/HG')
 

# Annotate the hard copy with information on which data files it used to create the plot
plt.figure(1)
plt.annotate(name, xy=(0.0, -1.0), xycoords='axes fraction')


plt.figure(2)
plt.annotate(name, xy=(0.0, -1.0), xycoords='axes fraction')

show()
