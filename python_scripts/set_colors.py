import matplotlib, random
def set_colors(NumColors=8):
    import matplotlib, random
    cc = [0] * NumColors
    for item in range(NumColors):
        cc[item] = ( (item) * 256 / NumColors)
        random.shuffle(cc)
    rcParams['axes.color_cycle'] = list(cm.hsv(cc))
    rcParams['lines.linewidth'] = 2



    
