from turtle import *
from math import *
import sys
import csv

f = open("file.csv")

data = list(csv.reader(f, delimiter=';'))
for x in data:
    x[0] = int(x[0])
    x[1] = int(x[1])
width, height = data[0]
data = data[1:]

sys.setrecursionlimit(len(data))

tracer = []
actual = []

print("height : "+str(height))
print("width : "+str(width))
maxDist = round((width+height)/512)
print("default maxDist selected : "+str(maxDist))

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

setworldcoordinates(-width, -height, width, height)
setpos(0,0)
for a in tracer:
    if len(a) >= 5:
        penup()
        pp = a[0]
        setpos(pp[0], -pp[1])
        pendown()
        for p in a:
            setpos(p[0], -p[1])
mainloop()