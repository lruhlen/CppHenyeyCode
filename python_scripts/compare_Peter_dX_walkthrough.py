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
savedirBase =  eg.diropenbox(msg='Pick the first Peter run you want to analyze',default='/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/2013/')
savedirBase += '/'
filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_G*.txt'):
        filelist.append(file)
fileHelenaG = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_C*.txt'):
        filelist.append(file)
fileHelenaC = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_D*.txt'):
        filelist.append(file)
fileHelenaD = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_E*.txt'):
        filelist.append(file)
fileHelenaE = savedirBase+(str(filelist[0]))

HC = numpy.loadtxt(fileHelenaC,skiprows=1)[:,1:]
HD = numpy.loadtxt(fileHelenaD,skiprows=1)[:,1:]
HE = numpy.loadtxt(fileHelenaE,skiprows=1)[:,1:]
HG = numpy.loadtxt(fileHelenaG,skiprows=1)[:,1:]

#filePeterG = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/g_values.txt'
#filePeterG = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_gvalues.txt'
#filePeterG = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_debugging/full_nabla_calcs/dTime_1e8/G_values.txt'
savedirBase =  eg.diropenbox(msg='Pick the second Peter run you want to analyze',default='/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/2013/')
savedirBase += '/'
filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_G*.txt'):
        filelist.append(file)
filePeterG = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_C*.txt'):
        filelist.append(file)
filePeterC = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_D*.txt'):
        filelist.append(file)
filePeterD = savedirBase+(str(filelist[0]))

filelist = [ ]
for file in os.listdir(savedirBase):
    if fnmatch.fnmatch(file,'*_E*.txt'):
        filelist.append(file)
filePeterE = savedirBase+(str(filelist[0]))

PC = numpy.loadtxt(filePeterC,skiprows=1)[:,1:]
PD = numpy.loadtxt(filePeterD,skiprows=1)[:,1:]
PE = numpy.loadtxt(filePeterE,skiprows=1)[:,1:]
PG = numpy.loadtxt(filePeterG,skiprows=1)[:,1:]



#============================================================
# Declare constants to help with the calculations
# and plotting
#============================================================
#Color1 = cm.spectral(50)
#Color2 = cm.spectral(0)
#Color3 = cm.Dark2(110)
#Color4 = cm.Dark2(35)

#jMax = HC.shape[0]
jMax=551
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
HG =  numpy.reshape(HG,[jMax,iMax])
HC =  numpy.reshape(HC,[jMax,iMax,iMax])
HD =  numpy.reshape(HD,[jMax,iMax,iMax])
HE =  numpy.reshape(HE,[jMax,iMax,iMax])

PG = numpy.reshape(PG,[jMax,iMax])
PC = numpy.reshape(PC,[jMax,iMax,iMax])
PD = numpy.reshape(PD,[jMax,iMax,iMax])
PE = numpy.reshape(PE,[jMax,iMax,iMax])

# Following lines are kludges
#PG[-1] = HG[-1]
#HD[-1] = PD[-1]
#PD[-1,1] = [0.,1.,0.,0.]
#PD[-1,2] = [0.,0.,1.,0.]
#PD[-1,2,0] = 0.
#PD[-1,2,1] = 0.
#PD[-1,2,3] = 0.

#PD[-1,1,0] = 0.
#PD[-1,1,3] = 0.
##============================================================
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
        HS[j] = HD[j].T
        HSum[j] = HG[j]

        PS[j] = PD[j].T
        PSum[j] = PG[j]
    else:
        HS[j] = dot(HC[j].T,HB[j-1]) + HD[j].T
        HSum[j] = dot(HC[j].T,HA[j-1]) + HG[j]

        PS[j] = dot(PC[j].T,PB[j-1]) + PD[j].T
        PSum[j] = dot(PC[j].T,PA[j-1]) + PG[j]

    HA[j] = -1.0 * dot( inv(HS[j]) , HSum[j])
    HB[j] = -1.0 * dot( inv(HS[j]) , HE[j].T)
    
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


tempH = numpy.zeros((jMax,iMax))
tempP = numpy.zeros((jMax,iMax))

jrange = -1*(numpy.array(range(jMax-1)) + 2)
for j in jrange:
    tempH[j] =  dot(HB[j],HdX[j+1])
    tempP[j] =  dot(PB[j],PdX[j+1])
    
    HdX[j] = dot(HB[j],HdX[j+1]) + HA[j]
    PdX[j] = dot(PB[j],PdX[j+1]) + PA[j]
    otherHdX[j] = dot(HB[j],otherHdX[j+1]) + HA[j]
    otherPdX[j] = dot(PB[j],otherPdX[j+1]) + PA[j]
    #sys.exit(0)
#============================================================
# Plot the results
#============================================================
File1 = fileHelenaG.split('Research')[-1]
File2 = filePeterG.split('Research')[-1]
date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+File1+"\n"+File2

clf()

for i in range(4):
    plt.figure(i)
    plt.subplots_adjust(wspace=0.3,hspace=0.3)
    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.15)

    #    plt.subplot(3,1,1)
    plt.title(plotNames[i])
    plot(HdX[:,i],label='Peter1')
    plot(PdX[:,i],label='Peter2')
    legend(loc="best",prop={'size':10})

#    plt.subplot(3,1,2)
#    plot(otherHdX[:,i],label='Modified Peter1')
#    plot(PdX[:,i],label='Peter2')
#    legend(loc="best",prop={'size':10})
#
#    plt.subplot(3,1,3)
#    plot(HdX[:,i],label='Peter1')
#    plot(otherPdX[:,i],label='Modified Peter2')
#    plt.xlabel('Mass Cell Number')
#    legend(loc="best",prop={'size':10})
    plt.annotate(name, xy=(0.5, 0.01), xycoords='figure fraction',horizontalalignment='center',fontsize=10, bbox=dict(fc='white', ec='black'))

    

#plt.figure(5)
#plt.title('G1')
#plot(HG[:,0])
#plot(PG[:,0])
#
#plt.figure(6)
#plt.title('G2')
#plot(HG[:,1])
#plot(PG[:,1])
#
#plt.figure(7)
#plt.title('G3')
#plot(HG[:,2])
#plot(PG[:,2])
#
#plt.figure(8)
#plt.title('G4')
#plot(HG[:,3])
#plot(PG[:,3])

show()
