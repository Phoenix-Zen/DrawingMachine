
from turtle import *
from math import *
from PIL import Image, ImageDraw
img = Image.open("heart.jpeg")
img = img.convert('L')
img.save("image.jpeg", "jpeg")
points = []
width, height = img.size
around = 2
numberPixAround = 1
minToCount = 1


for x in range(width):
    for y in range(height):
        found = 0
        act = img.getpixel((x, y))
        for x1 in range(-around, around+1):
            for y1 in range(-around, around+1):
                if (x1 != 0 or y1 != 0) and (x+x1) >= 0 and (x+x1) < width and (y+y1) >= 0 and (y+y1) < height:
                    pix = img.getpixel((x+x1, y+y1))
                    if(abs(act-pix) <= minToCount):
                        found+=1
        if found <= numberPixAround:
            img.putpixel((x, y), 255)
            points.append((x, y))
        else:
            img.putpixel((x, y), 0)
print(len(points))
img.show()
img.save("image.jpeg", "jpeg")
trace = []
print(len(points))

for a in range(round(len(points)/2)-1):
    points.pop(a)

print(len(points))
newImg = Image.new('L', (width,height), color = 'white')
for p in points:
    newImg.putpixel(p, 0)
newImg.save("imageNew.jpeg", "jpeg")
fileWrite = open("file.csv", 'w')
fileWrite.write(str(width)+";"+str(height)+"\n")
for a in points:
    fileWrite.write(str(a[0])+";"+str(a[1])+"\n")
fileWrite.close()

