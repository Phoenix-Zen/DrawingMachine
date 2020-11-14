from PIL import Image
from edges import *
from turtle import *

imageFile = "../pics/glo.png"
image = Image.open(imageFile)
width, height = image.size
setworldcoordinates(0, 0, width, -height)

lines = findEdges(imageFile, deleteRange = 1, neighbourRange = 3)

for line in lines:
    up()
    setpos(line[0][0], line[0][1] - height)
    down()
    for point in line:
        setpos(point[0], point[1] - height)

exitonclick()