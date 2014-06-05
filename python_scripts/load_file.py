def load_file(BaseName=''):
    import easygui as eg
    import atpy
    File = eg.fileopenbox(msg='Pick the file you want to anaylze',default='/Users/laurel/Desktop/Research/'+BaseName)
    F=atpy.Table(File,type='ascii')
    return {'Data':F,'FileName':File}
