def make_annotation(arg1='',arg2=''):

    import string, datetime
    import matplotlib.pyplot as plt


    if (arg1=='') and (arg2==''):
        fileID = ''
    elif (arg1 != '') and (arg2 == ''):
        fileID = '\n from this file:\n'+arg1
    else:
        fileID = '\n from these files:\n'+arg1+'\n'+arg2

    date = datetime.datetime.today()
    date = date.strftime("%b-%d-%Y") 
    name = 'This plot was created on '+date+fileID
    plt.annotate(name, xy=(0.5, 0.01), xycoords='figure fraction',horizontalalignment='center',fontsize=10, bbox=dict(fc='white', ec='black'))

    return name
