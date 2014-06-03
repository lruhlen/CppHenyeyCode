constval = (63./4.) * (G*msun)**1.5 * msun * Rp**5.0 * ecc**2.0 / Qp
Pmin = 1e25
Pmax = 1e28


###############################################
youngerFile = eg.fileopenbox(msg='Pick a run directory to examine',default='/Users/laurel/Desktop/Research/BodenheimerCode/Code_for_Kozai/outputs/2013/May/')
younger = atpy.Table(youngerFile,type='ascii')

olderFile = eg.fileopenbox(msg='Pick a run directory to examine',default='/Users/laurel/Desktop/Research/BodenheimerCode/Code_for_Kozai/outputs/2013/May/')
older = atpy.Table(olderFile,type='ascii')

plt.subplot(2,2,1)
plt.grid(True)
plt.ylabel('Pressure')
plot(younger.M,younger.P,'-o',label='Start age = 3e7 yrs')
plot(older.M,older.P,label='Start age = 3e8 yrs')
legend()

plt.subplot(2,2,2)
plt.grid(True)
plt.ylabel('Radius')
plot(younger.M,younger.R,'-o')
plot(older.M,older.R)

plt.subplot(2,2,3)
plt.xlabel('Mass (g)')
plt.grid(True)
plt.ylabel('Luminosity')
plot(younger.M,younger.L,'-o')
plot(older.M,older.L)

plt.subplot(2,2,4)
plt.grid(True)
plt.xlabel('Mass (g)')
plt.ylabel('Temperature')
plot(younger.M,younger.T,'-o')
plot(older.M,older.T)

Teff = eg.enterbox('Teff = ?')
Lum = eg.enterbox('Lum = ? (in units of Lsun)')
foo = '1 Mjup, sigma = 100, j0 = 0, efac = 10\n R = 1.4 Rjup, Lum = '+Lum+' Lsun, Teff = '+Teff+' K'
plt.suptitle(foo)


#=====================================================

HelenaFile =  eg.fileopenbox(msg='Pick the HELENA file you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/2013/Mar/')
Hname = HelenaFile.split('Research')[-1]
Hname = Hname.split('iter')[0]
date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+Hname
H  = atpy.Table(HelenaFile,type='ascii')

plt.subplot(2,2,1)
plot(H.J,H.dP)
plt.subplot(2,2,2)
plot(H.J,H.dr)
plt.subplot(2,2,3)
plot(H.J,H.dL)
plt.subplot(2,2,4)
plot(H.J,H.dT)

plt.annotate(name, xy=(-0.1, -0.4), xycoords='axes fraction',horizontalalignment='center',fontsize=10, bbox=dict(fc='white', ec='black'))





HelenaFile =  eg.fileopenbox(msg='Pick the HELENA file you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/2013/Mar/')
H=atpy.Table(HelenaFile,type='ascii')

plt.figure(1)
plt.subplot(3,1,1)
plt.suptitle('Pressure')
plot(H.J,H.dP)
plt.title('dP raw')
plt.subplot(3,1,2)
plt.title('dP rescaled')
plot(H.J,H.dPrescaled)
plt.subplot(3,1,3)
plt.title('P')
plot(H.J,H.P)

plt.figure(2)
plt.subplot(3,1,1)
plt.suptitle('Radius')
plot(H.J,H.dr)
plt.title('dr raw')
plt.subplot(3,1,2)
plt.title('dr rescaled')
plot(H.J,H.drrescaled)
plt.subplot(3,1,3)
plt.title('r')
plot(H.J,H.r)


plt.figure(3)
plt.subplot(3,1,1)
plt.suptitle('Luminosity')
plot(H.J,H.dL)
plt.title('dL raw')
plt.subplot(3,1,2)
plt.title('dL rescaled')
plot(H.J,H.dLrescaled)
plt.subplot(3,1,3)
plt.title('L')
plot(H.J,H.L)


plt.figure(4)
plt.subplot(3,1,1)
plt.suptitle('Temperature')
plot(H.J,H.dT)
plt.title('dT raw')
plt.subplot(3,1,2)
plt.title('dT rescaled')
plot(H.J,H.dTrescaled)
plt.subplot(3,1,3)
plt.title('T')
plot(H.J,H.T)

#======================================================
run set_colors.py
run make_annotation.py
set_colors(5)

def plotstuff():
    Fname = '/BodenheimerCode/Code_for_Kozai/outputs/2013/April/'
    File = eg.fileopenbox(msg='Pick the file you want to anaylze',default='/Users/laurel/Desktop/Research/'+Fname)
    F=atpy.Table(File,type='ascii')

    Fname = string.join(File.split('Research')[-1].split('/')[1:],'/')
    ID= File.split('/')[-1]
    #    ID = Fname

    plt.figure(1)
    plt.subplot(2,2,1)
    plt.title('P')
    plot(F.J,F.P,label=ID)
    #    make_annotation(Fname)
    #    plt.legend(loc="best",prop={'size':10})

    #    plt.figure(2)
    plt.subplot(2,2,2)
    plt.title('r')
    plot(F.J,F.R,label=ID)
    #    make_annotation(Fname)
    #    plt.legend(loc="best",prop={'size':10})

    #    plt.figure(3)
    plt.subplot(2,2,3)
    plt.title('L')
    plot(F.J,F.L,label=ID)
    #    make_annotation(Fname)
    #    plt.legend(loc="best",prop={'size':10})
    
    #    plt.figure(4)
    plt.subplot(2,2,4)
    plt.title('T')
    plot(F.J,F.T,label=ID)
    make_annotation()
    plt.legend(loc="best",prop={'size':10})

#======================================================
def plotdXs():
    Fname = '/BodenheimerCode/UnalteredCode/outputs/2013/March/March_25_2013/v9/'
    File = eg.fileopenbox(msg='Pick the file you want to anaylze',default='/Users/laurel/Desktop/Research/'+Fname)
    F=atpy.Table(File,type='ascii')

    #    Fname = string.join(File.split('Research')[-1].split('/')[1:-1],'/')
    Fname = string.join(File.split('Research')[-1].split('/')[1:],'/')
    ID = Fname

    plt.figure(1)
    plt.subplot(2,2,1)
    plt.title('dP')
    plot(F.J,F.dP,label=ID)

    plt.subplot(2,2,2)
    plt.title('dr')
    plot(F.J,F.dr,label=ID)

    plt.subplot(2,2,3)
    plt.title('dL')
    plot(F.J,F.dL,label=ID)

    plt.subplot(2,2,4)
    plt.title('dT')
    plot(F.J,F.dT,label=ID)
    make_annotation()
    plt.legend(loc="best",prop={'size':10})

#======================================================
Fname = '/BodenheimerCode/UnalteredCode/outputs/2013/March/March_11_2013/'
plt.legend(loc='lower center',ncol=6,prop={'size':10})
def plot_dLs():
    foo = load_file(Fname)
    Data = foo['Data']
    FileName = foo['FileName']
    ForAnnotation = string.join(FileName.split('Research')[-1].split('/')[1:-1],'/')
    ForLegend =  FileName.split('/')[-1].split('.txt')[-2]

    plot(Data.J,Data.dLrescaled/Data.L,label=ForLegend)
    plt.legend(loc="best")

#======================================================
def plot_Ls():
    foo = load_file(Fname)
    Data = foo['Data']
    FileName = foo['FileName']
    ForAnnotation = string.join(FileName.split('Research')[-1].split('/')[1:-1],'/')
    ForLegend =  FileName.split('/')[-1].split('.txt')[-2]

    plot(Data.J,Data.L,label=ForLegend)
    plt.legend(loc="best",ncol=4,prop={'size':10})
#======================================================

origName = '/BodenheimerCode/UnalteredCode/outputs/2013/March/March_5_2013/v1/'
alterName = '/BodenheimerCode/UnalteredCode/outputs/2013/March/March_8_2013/'

date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from the data in these directories:\n'+origName+'\n'+alterName

plt.subplots_adjust(wspace=0.3,hspace=0.3,left=0.1, right=0.9, top=0.9, bottom=0.15)
                    
orig = eg.fileopenbox(msg='Pick the original (Peter) file you want to anaylze',default='/Users/laurel/Desktop/Research'+origName)
orig=atpy.Table(orig,type='ascii')

alter = eg.fileopenbox(msg='Pick the altered (Peter) file you want to anaylze',default='/Users/laurel/Desktop/Research'+alterName)
alter= atpy.Table(alter,type='ascii')


plt.figure(1)
plt.subplots_adjust(wspace=0.3,hspace=0.4,left=0.1, right=0.9, top=0.9, bottom=0.15)
plt.suptitle('dP comparison')
plt.subplot(3,1,1)
plt.title('orig eostable')
plot(orig.J,orig.dP)
plt.subplot(3,1,2)
plt.title('altered-up eostable')
plot(alter.J,alter.dP)
plt.subplot(3,1,3)
plt.title('P profile')
plot(orig.J,orig.P)
plt.annotate(name, xy=(0.1, -0.5), xycoords='axes fraction',horizontalalignment='left',fontsize=10,bbox=dict(fc='white', ec='black'))

plt.figure(2)
plt.subplots_adjust(wspace=0.3,hspace=0.4,left=0.1, right=0.9, top=0.9, bottom=0.15)
plt.suptitle('dr comparison')
plt.subplot(3,1,1)
plt.title('orig eostable')
plot(orig.J,orig.dr)
plt.subplot(3,1,2)
plt.title('altered-up eostable')
plot(alter.J,alter.dr)
plt.subplot(3,1,3)
plt.title('r profile')
plot(orig.J,orig.r)
plt.annotate(name, xy=(0.1, -0.5), xycoords='axes fraction',horizontalalignment='left',fontsize=10,bbox=dict(fc='white', ec='black'))

plt.figure(3)
plt.subplots_adjust(wspace=0.3,hspace=0.4,left=0.1, right=0.9, top=0.9, bottom=0.15)
plt.suptitle('dL comparison')
plt.subplot(3,1,1)
plt.title('orig eostable')
plot(orig.J,orig.dL)
plt.subplot(3,1,2)
plt.title('altered-up eostable')
plot(alter.J,alter.dL)
plt.subplot(3,1,3)
plt.title('L profile')
plot(alter.J,orig.L)
plt.annotate(name, xy=(0.1, -0.5), xycoords='axes fraction',horizontalalignment='left',fontsize=10,bbox=dict(fc='white', ec='black'))

plt.figure(4)
plt.subplots_adjust(wspace=0.3,hspace=0.4,left=0.1, right=0.9, top=0.9, bottom=0.15)
plt.suptitle('dT comparison')
plt.subplot(3,1,1)
plt.title('orig eostable')
plot(orig.J,orig.dT)
plt.subplot(3,1,2)
plt.title('altered-up eostable')
plot(alter.J,alter.dT)
plt.subplot(3,1,3)
plt.title('T profile')
plot(orig.J,orig.T)
plt.annotate(name, xy=(0.1, -0.5), xycoords='axes fraction',horizontalalignment='left',fontsize=10,bbox=dict(fc='white', ec='black'))

#======================================================
fignum=1
for i in range(4):
    for k in range(4):
        print 'i=',i+1,' k=',k+1
        plt.figure(fignum)
        plt.suptitle('Dmatrix: i='+str(i+1)+' k='+str(k+1))
        plt.subplot(2,1,1)
        plot(HD[:,i,k]-PD[:,k,i])
        plt.subplot(2,1,2)
        plot(HD[:,i,k])
        plot(PD[:,k,i])
        fignum = fignum+1
#======================================================

H=load_file()
HAnnot = string.join(H['FileName'].split('Research')[-1].split('/')[1:-1],'/')
HLeg =  H['FileName'].split('/')[-1].split('.txt')[-2]

P=load_file()
PAnnot = string.join(P['FileName'].split('Research')[-1].split('/')[1:-1],'/')
PLeg =  P['FileName'].split('/')[-1].split('.txt')[-2]

plt.figure(1)
plt.title('dP')
plot(H['Data'].dP,label=HLeg)
plot(P['Data'].dP,label=PLeg)
legend(loc="best")
make_annotation(HAnnot,PAnnot)

plt.figure(2)
plt.title('dr')
plot(H['Data'].dr,label=HLeg)
plot(P['Data'].dr,label=PLeg)
legend(loc="best")
make_annotation(HAnnot,PAnnot)

plt.figure(3)
plt.title('dL')
plot(H['Data'].dL,label=HLeg)
plot(P['Data'].dL,label=PLeg)
legend(loc="best")
make_annotation(HAnnot,PAnnot)

plt.figure(4)
plt.title('dT')
plot(H['Data'].dT,label=HLeg)
plot(P['Data'].dT,label=PLeg)
legend(loc="best")
make_annotation(HAnnot,PAnnot)


##############
#//    J       dM         M         P        R            L         T         RHO    1-BETA     HYDR     HE4       D        N        O
date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 

F = load_file()
InFileName = F['FileName']
OutFileName = string.join(InFileName.split('/')[:-1],'/') + '/for_Helena_read_in.txt'
F = F['Data']


table_len = max(F.J)
F.J = F.J[::-1]
F.dM = F.dM[::-1]
F.M = F.M[::-1]
F.P = F.P[::-1]
F.r = F.r[::-1]
F.L = F.L[::-1]
F.T = F.T[::-1]
F.rho = F.rho[::-1]


header = InFileName.split('Research')[-1]
header = '// Created from '+header+' on '+date+'\n'
header += '//    J       dM         M         P        R            L         T         RHO \n'

fout = open(OutFileName,'w')
fout.write(header)

for index in range(table_len):
    line = str(F.J[index])+'   '+str(F.dM[index])+'   '+str(F.M[index])+'   '+str(F.P[index])+'   '+str(F.r[index])+'   '+str(F.L[index])+'   '+str(F.T[index])+'   '+str(F.rho[index])+'\n'
    #    print line
    fout.write(line)

fout.close()
    
