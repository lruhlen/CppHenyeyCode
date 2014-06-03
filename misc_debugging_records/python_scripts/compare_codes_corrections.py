#============================================================
# Import modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime

#============================================================
# Declare useful physical constants for later
#============================================================
Color1 = cm.spectral(0)
Color2 = cm.Dark2(3)
RatioColor = cm.Dark2(110)

File1 = eg.fileopenbox('Pick the PETER file you want to use',default='/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/')
label1 = 'Peter'

File2 = eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
filelist = [ ]
for file in os.listdir(File2):
    if fnmatch.fnmatch(file,'*_dX_*.txt'):
        filelist.append(file)
File2 = File2+"/"+(str(filelist[0]))

label2 = 'Helena'

date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 

suptitleString = ' '

#============================================================
# Parse the input command-line args (if any)
#============================================================


#============================================================
# Set up the multiplot layout for this data
#============================================================
plt.close('all')
plt.clf()
#plt.figure(1, figsize=(10, 8))
matplotlib.rc('xtick', labelsize=10) 
matplotlib.rc('ytick', labelsize=10) 
plt.subplots_adjust(wspace=0.3,hspace=0.3)
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

# A little something to format the legend properly...
params = {'legend.linewidth': 0.25}
rcParams.update(params)

#============================================================
# Read in the data
#============================================================
pd = asciitable.read(File1,guess=False)
hd = asciitable.read(File2,guess=False)

#============================================================
# Assign names to the data columns
#============================================================
pdCell = numpy.array(pd['MassCellNumber'][0:])
pindex = pdCell.argsort()
pdCell = pdCell[pindex]

pd_dP_raw = numpy.array(pd['dP'][pindex])
pd_dr_raw = numpy.array(pd['dr'][pindex])
pd_dL_raw = numpy.array(pd['dL'][pindex])
pd_dT_raw = numpy.array(pd['dT'][pindex])
pd_dP_scaled = numpy.array(pd['dPrescaled'][pindex])
pd_dr_scaled = numpy.array(pd['drrescaled'][pindex])
pd_dL_scaled = numpy.array(pd['dLrescaled'][pindex])
pd_dT_scaled = numpy.array(pd['dTrescaled'][pindex])
pd_P = numpy.array(pd['P'][pindex])
pd_r = numpy.array(pd['r'][pindex])
pd_L = numpy.array(pd['L'][pindex])
pd_T = numpy.array(pd['T'][pindex])

hdCell = numpy.array(hd['MassCellNumber'][0:])
hindex = hdCell.argsort()
hdCell = hdCell[hindex]

hd_dP_raw = numpy.array(hd['dP'][hindex])
hd_dr_raw = numpy.array(hd['dr'][hindex])
hd_dL_raw = numpy.array(hd['dL'][hindex])
hd_dT_raw = numpy.array(hd['dT'][hindex])
hd_dP_scaled = numpy.array(hd['dPrescaled'][hindex])
hd_dr_scaled = numpy.array(hd['drrescaled'][hindex])
hd_dL_scaled = numpy.array(hd['dLrescaled'][hindex])
hd_dT_scaled = numpy.array(hd['dTrescaled'][hindex])
hd_P = numpy.array(hd['P'][hindex])
hd_r = numpy.array(hd['r'][hindex])
hd_L = numpy.array(hd['L'][hindex])
hd_T = numpy.array(hd['T'][hindex])
#sys.exit(1)
#============================================================
# Plot the data, and ask the user if they want to save
# a hardcopy of each plot-set
#============================================================
# plt.figure(1)
# clf()
# plt.subplots_adjust(wspace=0.3,hspace=0.3)
# plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
# 
# plt.subplot(2,2,1)
# plt.suptitle(suptitleString)
# plot(pdCell,pd_P,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_P,c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('P')
# legend(loc='best',prop={'size':6})
# 
# plt.subplot(2,2,2)
# plot(pdCell,pd_r,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_r, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('r')
# 
# plt.subplot(2,2,3)
# plot(pdCell,pd_L,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_L, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('L')
# plt.xlabel('Mass Cell Number')
# 
# plt.subplot(2,2,4)
# plot(pdCell,pd_T,c=Color1,linewidth=1.5)
# plot(hdCell,hd_T, c=Color2,linewidth=1.5)
# plt.ylabel('T')
# plt.xlabel('Mass Cell Number')
# 
# # Annotate the hard copy with information on which data files it used to create the plot
# legend([File1,File2], loc = 'center left', bbox_to_anchor = (-1.5, -0.45),prop={'size':8},title='This plot was created on '+date+' from these data files:')
# show()
#  
#  #if eg.ynbox(msg='Do you want to save this plot as a jpg?'): #Prompt the user
#  #    if not os.path.exists(SaveDir):  #Create the save-directory if it doesn't already exist
#  #        os.makedirs(SaveDir)
#  #    SaveName = SaveDir + 'X_val_comparison.jpg'
#  #    savefig(SaveName)
#  #
 ###
plt.figure(2)
clf()
plt.subplots_adjust(wspace=0.3,hspace=0.3)
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

plt.subplot(2,2,1)
plt.suptitle(suptitleString)
plot(pdCell,pd_dP_raw,c=Color1,label=label1,linewidth=1.5)
plot(hdCell,hd_dP_raw, c=Color2,label=label2,linewidth=1.5)
plt.ylabel('dP_raw')
legend(loc='best',prop={'size':6})

plt.subplot(2,2,2)
plot(pdCell,pd_dr_raw,c=Color1,label=label1,linewidth=1.5)
plot(hdCell,hd_dr_raw, c=Color2,label=label2,linewidth=1.5)
plt.ylabel('dr_raw')

plt.subplot(2,2,3)
plot(pdCell,pd_dL_raw,c=Color1,label=label1,linewidth=1.5)
plot(hdCell,hd_dL_raw, c=Color2,label=label2,linewidth=1.5)
plt.ylabel('dL_raw')
plt.xlabel('Mass Cell Number')

plt.subplot(2,2,4)
plot(pdCell,pd_dT_raw,c=Color1,label=label1,linewidth=1.5)
plot(hdCell,hd_dT_raw, c=Color2,label=label2,linewidth=1.5)
plt.ylabel('dT_raw')
plt.xlabel('Mass Cell Number')

legend([File1,File2], loc = 'center left', bbox_to_anchor = (-1.7, -0.45),prop={'size':8},title='This plot was created on '+date+' from these data files:')
show()

# # if eg.ynbox(msg='Do you want to save this plot as a jpg?'): #Prompt the user
# #     if not os.path.exists(SaveDir):  #Create the save-directory if it doesn't already exist
# #         os.makedirs(SaveDir)
# #     SaveName = SaveDir + 'dX_raw_comparison.jpg'
# #     # Annotate the hard copy with information on which data files it used to create the plot
# #     savefig(SaveName)
# # 
# 
# ###
#plt.figure(3)
#clf()
#plt.subplots_adjust(wspace=0.3,hspace=0.3)
#plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
#
#plt.subplot(2,2,1)
#plt.suptitle(suptitleString)
#plot(pdCell,pd_dP_scaled,c=Color1,label=label1,linewidth=1.5)
#plot(hdCell,hd_dP_scaled, c=Color2,label=label2,linewidth=1.5)
#plt.ylabel('dP_scaled')
#legend(loc='best',prop={'size':6})
#
#plt.subplot(2,2,2)
#plot(pdCell,pd_dr_scaled,c=Color1,label=label1,linewidth=1.5)
#plot(hdCell,hd_dr_scaled, c=Color2,label=label2,linewidth=1.5)
#plt.ylabel('dr_scaled')
#
#plt.subplot(2,2,3)
#plot(pdCell,pd_dL_scaled,c=Color1,label=label1,linewidth=1.5)
#plot(hdCell,hd_dL_scaled, c=Color2,label=label2,linewidth=1.5)
#plt.ylabel('dL_scaled')
#plt.xlabel('Mass Cell Number')
#
#plt.subplot(2,2,4)
#plot(pdCell,pd_dT_scaled,c=Color1,label=label1,linewidth=1.5)
#plot(hdCell,hd_dT_scaled, c=Color2,label=label2,linewidth=1.5)
#plt.ylabel('dT_scaled')
#plt.xlabel('Mass Cell Number')
#
#legend([File1,File2], loc = 'center left', bbox_to_anchor = (-1.5, -0.45),prop={'size':8},title='This plot was created on '+date+' from these data files:')
#show()
## # 
# # if eg.ynbox(msg='Do you want to save this plot as a jpg?'): #Prompt the user
# #     if not os.path.exists(SaveDir):  #Create the save-directory if it doesn't already exist
# #         os.makedirs(SaveDir)
# #     SaveName = SaveDir + 'dX_scaled_comparison.jpg'
# #     # Annotate the hard copy with information on which data files it used to create the plot
# #     savefig(SaveName)
# # 
# ###
plt.figure(4)
clf()
plt.subplots_adjust(wspace=0.3,hspace=0.3)
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

plt.subplot(2,2,1)
plt.suptitle(suptitleString)
plot(hd_dP_raw/pd_dP_raw ,'-s',markersize=4.0,c=RatioColor,label=label2+'_raw / '+label1+'_raw')
plt.ylabel('dP_raw')
legend(loc='best',prop={'size':6})

plt.subplot(2,2,2)
plot(hd_dr_raw/pd_dr_raw ,'-s',markersize=4.0,c=RatioColor)
plt.ylabel('dr_raw')

plt.subplot(2,2,3)
plot(hd_dL_raw/pd_dL_raw ,'-s',markersize=4.0,c=RatioColor)
plt.ylabel('dL_raw')
plt.xlabel('Mass Cell Number')

plt.subplot(2,2,4)
plot(hd_dT_raw/pd_dT_raw ,'-s',markersize=4.0,c=RatioColor)
plt.ylabel('dT_raw')
plt.xlabel('Mass Cell Number')

# Annotate the hard copy with information on which data files it used to create the plot
legend([File1+'\n'+File2], loc = 'center left', bbox_to_anchor = (-1.7, -0.45),prop={'size':8},title='This plot was created on '+date+' from these data files:')

show()
 
# # if eg.ynbox(msg='Do you want to save this plot as a jpg?'): #Prompt the user
# #     if not os.path.exists(SaveDir):  #Create the save-directory if it doesn't already exist
# #         os.makedirs(SaveDir)
# #     SaveName = SaveDir + 'raw_dX_ratios.jpg'
# #     savefig(SaveName)
# # 
# ###
# plt.figure(5)
# clf()
# plt.subplots_adjust(wspace=0.3,hspace=0.3)
# plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
# 
# plt.subplot(2,2,1)
# plt.suptitle(suptitleString)
# plot(hd_dP_scaled/pd_dP_scaled ,'-s',markersize=4.0,c=RatioColor,label=label2+'_scaled / '+label1+'_scaled')
# plt.ylabel('dP_scaled ratio')
# legend(loc='best',prop={'size':10})
# 
# plt.subplot(2,2,2)
# plot(hd_dr_scaled/pd_dr_scaled ,'-s',markersize=4.0,c=RatioColor)
# plt.ylabel('dr_scaled ratio')
# 
# plt.subplot(2,2,3)
# plot(hd_dL_scaled/pd_dL_scaled ,'-s',markersize=4.0,c=RatioColor)
# plt.ylabel('dL_scaled ratio')
# plt.xlabel('Mass Cell Number')
# 
# plt.subplot(2,2,4)
# plot(hd_dT_scaled/pd_dT_scaled ,'-s',markersize=4.0,c=RatioColor)
# plt.ylabel('dT_scaled ratio')
# plt.xlabel('Mass Cell Number')
# 
# # Annotate the hard copy with information on which data files it used to create the plot
# legend([File1+'\n'+File2], loc = 'center left', bbox_to_anchor = (-1.5, -0.45),prop={'size':8},title='This plot was created on '+date+' from these data files:')
# 
# show()
# 
# #if eg.ynbox(msg='Do you want to save this plot as a jpg?'): #Prompt the user
# #    if not os.path.exists(SaveDir):  #Create the save-directory if it doesn't already exist
# #        os.makedirs(SaveDir)
# #    SaveName = SaveDir + 'scaled_dX_ratios.jpg'
# #    savefig(SaveName)
# #
# ###
# plt.figure(6)
# clf()
# plt.subplots_adjust(wspace=0.3,hspace=0.3)
# plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
# 
# plt.subplot(2,2,1)
# plt.suptitle(suptitleString)
# plot(pdCell,pd_dP_scaled/pd_P,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dP_scaled/hd_P, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dP_scaled / P')
# legend(loc='best',prop={'size':6})
# 
# plt.subplot(2,2,2)
# plot(pdCell,pd_dr_scaled/pd_r,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dr_scaled/hd_r, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dr_scaled / r')
# 
# plt.subplot(2,2,3)
# plot(pdCell,pd_dL_scaled/pd_L,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dL_scaled/hd_L, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dL_scaled / L')
# plt.xlabel('Mass Cell Number')
# 
# plt.subplot(2,2,4)
# plot(pdCell,pd_dT_scaled/pd_T,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dT_scaled/hd_P, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dT_scaled / T')
# plt.xlabel('Mass Cell Number')
# 
# # Annotate the hard copy with information on which data files it used to create the plot
# legend([File1,File2], loc = 'center left', bbox_to_anchor = (-1.5, -0.45),prop={'size':8},title='This plot was created on '+date+' from these data files:')
# show()
# 
# #if eg.ynbox(msg='Do you want to save this plot as a jpg?'): #Prompt the user
# #    if not os.path.exists(SaveDir):  #Create the save-directory if it doesn't already exist
# #        os.makedirs(SaveDir)
# #    SaveName = SaveDir + 'scaled_dX_over_X_comparison.jpg'
# #    savefig(SaveName)
# #
# ###
# plt.figure(7)
# clf()
# plt.subplots_adjust(wspace=0.3,hspace=0.3)
# plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
# 
# plt.subplot(2,2,1)
# plt.suptitle(suptitleString)
# plot(pdCell,pd_dP_raw/pd_P,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dP_raw/hd_P, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dP_raw / P')
# legend(loc='best',prop={'size':6})
# 
# plt.subplot(2,2,2)
# plot(pdCell,pd_dr_raw/pd_r,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dr_raw/hd_r, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dr_raw / r')
# 
# plt.subplot(2,2,3)
# plot(pdCell,pd_dL_raw/pd_L,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dL_raw/hd_L, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dL_raw / L ')
# plt.xlabel('Mass Cell Number')
# 
# plt.subplot(2,2,4)
# plot(pdCell,pd_dT_raw/pd_T,c=Color1,label=label1,linewidth=1.5)
# plot(hdCell,hd_dT_raw/hd_T, c=Color2,label=label2,linewidth=1.5)
# plt.ylabel('dT_raw / T')
# plt.xlabel('Mass Cell Number')
# 
# # Annotate the hard copy with information on which data files it used to create the plot
# legend([File1,File2], loc = 'center left', bbox_to_anchor = (-1.5, -0.45),prop={'size':8},title='This plot was created on '+date+' from these data files:')
# 
# show()
# 
# #if eg.ynbox(msg='Do you want to save this plot as a jpg?'): #Prompt the user
# #    if not os.path.exists(SaveDir):  #Create the save-directory if it doesn't already exist
# #        os.makedirs(SaveDir)
# #    SaveName = SaveDir + 'raw_dX_over_X_comparison.jpg'
# #    savefig(SaveName)
# #
