#============================================================
# Import modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime

print len(sys.argv)

if len(sys.argv) < 2:
    print "short list"
else:
    print "long list"


clf()
plt.subplots_adjust(wspace=0.3,hspace=0.3)
plt.subplots_adjust(left=0.12, right=0.97, top=0.9, bottom=0.2)

plt.subplot(4,1,1)
plt.ylabel("A1")
plot(HA[:,0]/PA[:,0],label='Helena / Peter',linewidth=4.0,color=cm.spring(20))
#plot(HA[:,0],label='Helena',linewidth=4.0,color=cm.spring(20))
#plot(PA[:,0],label='Peter',linewidth=4.0,color=cm.copper(2))

plt.subplot(4,1,2)
plt.ylabel("A2")
plot(HA[:,1]/PA[:,1],label='Helena / Peter',linewidth=4.0,color=cm.spring(20))
#plot(HA[:,1],label='Helena',linewidth=4.0,color=cm.spring(20))
#plot(PA[:,1],label='Peter',linewidth=4.0,color=cm.copper(2))

plt.subplot(4,1,3)
plt.ylabel("A3")
plot(HA[:,2]/PA[:,2],label='Helena / Peter',linewidth=4.0,color=cm.spring(20))
#plot(HA[:,2],label='Helena',linewidth=4.0,color=cm.spring(20))
#plot(PA[:,2],label='Peter',linewidth=4.0,color=cm.copper(2))

plt.subplot(4,1,4)
plt.ylabel("A4")
plot(HA[:,3]/PA[:,3],label='Helena / Peter',linewidth=4.0,color=cm.spring(20))
#plot(HA[:,3],label='Helena',linewidth=4.0,color=cm.spring(20))
#plot(PA[:,3],label='Peter',linewidth=4.0,color=cm.copper(2))
plt.annotate(name, xy=(0.5, -1.0), xycoords='axes fraction',horizontalalignment='center',fontsize=10)

plt.subplot(4,1,1)
legend(loc="best")
plt.suptitle('A-matrix values comparison calculated in compare_dX_walkthrough.py')
