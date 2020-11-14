from PIL import Image, ImageFilter
import sys
import csv
from turtle import *
from math import *

def renderImage(fileSrc, maxSize = 0, maxDist = 0, colorForWhite = 64, diminutionBegin = 0, lisageNumber = 0):
    
    def diminution(a):
        for x in range(round(len(a)/2)-1):
            a.pop(x)
        return a

    image = Image.open(fileSrc)
    image = image.convert('L')
    image = image.filter(ImageFilter.FIND_EDGES)

    if colorForWhite < 0 or colorForWhite > 256:
        colorForWhite = 64

    width, height = image.size
    if maxSize > 0:
        if width > maxSize or height > maxSize:
            ratio = min(maxSize/width, maxSize/height)
            image.thumbnail((width*ratio, height*ratio), Image.ANTIALIAS)
            print("resized")
            width, height = image.size

    fileWrite = open("file.csv", 'w')
    pixels = image.load()
    fileWrite.write(str(width)+";"+str(height)+"\n")
    a = 0
    image.save("filter.png")
    for x in range(width):
        for y in range(height):
            if pixels[x, y] >= colorForWhite:
                a+=1
                fileWrite.write(str(x)+";"+str(y)+"\n")
    print(a)
    fileWrite.close()

    print("finished edge conversion")

    f = open("file.csv")

    data = list(csv.reader(f, delimiter=';'))
    for x in data:
        x[0] = int(x[0])
        x[1] = int(x[1])
    width, height = data[0]
    data = data[1:]

    for e in range(diminutionBegin):
        diminution(data)

    sys.setrecursionlimit(len(data))

    tracer = []
    actual = []

    print("height : "+str(height))
    print("width : "+str(width))
    if maxDist == 0:
        maxDist = round((width+height)/512)
        print("default maxDist selected : "+str(maxDist))
    else:
        print("maxDist selected : "+str(maxDist))


    k = []

    for t1 in reversed(range(maxDist+1)):
        k1 = []
        for x1 in range(-maxDist, maxDist+1):
            for x2 in range(-maxDist, maxDist+1):
                if abs(x1)+abs(x2) == t1:
                    k1.append([x1, x2])
        k.append(k1)

    def managePoint(p):
        x = p[0]
        y = p[1]
        data.remove(p)
        actual.append(p)
        f = []
        for m1 in k:
            for m in m1:
                px = [x+m[0], y+m[1]]
                if px in data:
                    if f == []:
                        f = px
                    else:
                        data.remove(px)
        if f != []:
            managePoint(f)

    while len(data) != 0:
        print(str(len(data))+" lasting")
        actual = []
        managePoint(data[0])
        tracer.append(actual)

    def computeangle(x1, y1, x2, y2, x3, y3):
        """
        Calcule l'angle a partir de 3 points
        """
        import math

        a = ((x3-x1)**2+(y3-y1)**2)**0.5
        b = ((x2-x1)**2+(y2-y1)**2)**0.5
        c = ((x3-x2)**2+(y3-y2)**2)**0.5
        try:
            return math.acos((a**2+c**2-b**2)/(2*a*c))
        except ValueError:
            return 300

    def lisage(a, k):
        for b in range(k):
            for i in range(1, len(a)-1):
                angle = computeangle(a[i-1][0], a[i-1][1], a[i][0], a[i][1], a[i+1][0], a[i+1][1])
                if angle > pi/2:
                    a[i][0] = (a[i-1][0] + a[i+1][0])//2
                    a[i][1] = (a[i-1][1] + a[i+1][1])//2
        return
    setworldcoordinates(0, 0, width, height)
    setpos(0,0)
    for a in tracer:
        if len(a) >= 5:
            lisage(a, lisageNumber)
            a = diminution(a)
            penup()
            pp = a[0]
            setpos(pp[0], height-pp[1])
            pendown()
            for p in a:
                setpos(p[0], height-p[1])
    mainloop()