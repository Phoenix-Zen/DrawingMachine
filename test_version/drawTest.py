from edges import *
from turtle import *
from PIL import Image
import matplotlib.pyplot as plt

imageFile = "../pics/monkey.png"
image = Image.open(imageFile)
width, height = image.size
setworldcoordinates(0, 0, width, -height)

lines = findEdges(imageFile, threshold = 200, neighbourRange = 1, lineSmooth = 3, minimumLine = 5)

lines.sort(key = lambda l: l[0][0] + l[0][1], reverse = True)
while len(lines) > 0:
    line = lines.pop()
    up()
    goto(line[0][0], line[0][1] - height)
    down()
    for point in line:
        goto(point[0], point[1] - height)
    lines.sort(key = lambda l: abs(point[0] - l[0][0]) + abs(point[1] - l[0][1]), reverse = True)

exitonclick()