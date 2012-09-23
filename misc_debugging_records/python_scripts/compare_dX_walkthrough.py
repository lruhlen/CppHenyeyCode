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

savedirBase =  eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
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


#============================================================
# Declare constants to help with the calculations
# and plotting
#============================================================
Color1 = cm.spectral(50)
Color2 = cm.spectral(0)
Color3 = cm.Dark2(110)
Color4 = cm.Dark2(35)

jMax = HC.shape[0]
iMax = 4
plotNames = ['dP','dr','dL','dT']

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


#============================================================
# Start walking through the dX calculations,
# from the outside in.
#============================================================
HdX = numpy.zeros((jMax,iMax))
PdX = numpy.zeros((jMax,iMax))
otherHdX = numpy.zeros((jMax,iMax))
otherPdX = numpy.zeros((jMax,iMax))

HdX[-1] = HA[-1]
PdX[-1] = PA[-1]
otherHdX[-1] = PA[-1]
otherPdX[-1] = HA[-1]

jrange = -1*(numpy.array(range(jMax-1)) + 2)
for j in jrange:
    HdX[j] = dot(HB[j],HdX[j+1]) + HA[j]
    PdX[j] = dot(PB[j],PdX[j+1]) + PA[j]
    otherHdX[j] = dot(HB[j],otherHdX[j+1]) + HA[j]
    otherPdX[j] = dot(PB[j],otherPdX[j+1]) + PA[j]
    #sys.exit(0)
#============================================================
# Plot the results
#============================================================
File1 = savedirBase.split('Desktop')[-1]
File2 = filePeterG.split('Desktop')[-1]
date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+File1+"\n"+File2



for i in range(iMax):
    plt.figure(i+2)
    plt.subplots_adjust(wspace=0.3,hspace=0.3)
    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

    plt.suptitle(plotNames[i]+' profile comparison')
    plt.subplot(3,1,1)
    plot(HdX[:,i],linewidth=7.0,color=Color1,label='Helena')
    plot(PdX[:,i],linewidth=7.0,color=Color2,label='Peter')
    #    pylab.xlim([0,jMax])
    legend(loc="best",prop={'size':10})

    plt.subplot(3,1,2)
    plot(otherHdX[:,i],linewidth=7.0,color=Color4,label='Modified Helena')
    plot(PdX[:,i],linewidth=3.0,color=Color2,label='Peter')
    legend(loc="best",prop={'size':10})

    plt.subplot(3,1,3)
    plot(otherPdX[:,i],linewidth=7.0,color=Color3,label='Modified Peter')
    plot(HdX[:,i],linewidth=3.0,color=Color1,label='Helena')
    plt.xlabel('Mass Cell Number')
    legend(loc="best",prop={'size':10})
    
    plt.annotate(name, xy=(0.0, -1.0), xycoords='axes fraction')

    




show()
