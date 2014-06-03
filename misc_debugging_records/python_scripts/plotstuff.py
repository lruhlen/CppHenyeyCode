def plotstuff():
    Fname = '/BodenheimerCode/UnalteredCode/outputs/2013/March/'
    File = eg.fileopenbox(msg='Pick the file you want to anaylze',default='/Users/laurel/Desktop/Research/'+Fname)
    F=atpy.Table(File,type='ascii')

    Fname = string.join(File.split('Research')[-1].split('/')[1:-1],'/')
    #   ID= File.split('/')[-1].split('.txt')[-2]
    ID = Fname

    plt.figure(1)
    plt.subplot(2,2,1)
    plt.title('P')
    plot(F.J,F.P,label=ID)
    #    make_annotation(Fname)
    #    plt.legend(loc="best",prop={'size':10})

    #    plt.figure(2)
    plt.subplot(2,2,2)
    plt.title('r')
    plot(F.J,F.r,label=ID)
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
