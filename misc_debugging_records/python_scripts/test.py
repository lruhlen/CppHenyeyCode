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
plt.subplot(4,1,1)
plot(HA[:,0],label='Helena',linewidth=4.0,color=cm.spring(20))
plot(PA[:,0],label='Peter',linewidth=4.0,color=cm.copper(2))

plt.subplot(4,1,2)
plot(HA[:,1],label='Helena',linewidth=4.0,color=cm.spring(20))
plot(PA[:,1],label='Peter',linewidth=4.0,color=cm.copper(2))

plt.subplot(4,1,3)
plot(HA[:,2],label='Helena',linewidth=4.0,color=cm.spring(20))
plot(PA[:,2],label='Peter',linewidth=4.0,color=cm.copper(2))

plt.subplot(4,1,4)
plot(HA[:,3],label='Helena',linewidth=4.0,color=cm.spring(20))
plot(PA[:,3],label='Peter',linewidth=4.0,color=cm.copper(2))

plt.subplot(4,1,4)
legend(loc="best")
plt.suptitle('A value comparison calculated in compare_dX_walkthrough.py')
