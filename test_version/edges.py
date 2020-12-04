from math import acos, pi, floor, log10
from PIL import Image, ImageFilter

def findEdges(imageFile, threshold = 200, neighbourRange = 5, deleteRange = 3, joinRange = 5, lineReduce = -1, lineSmooth = 1, minimumLine = 10):
    image = Image.open(imageFile).convert("L").filter(ImageFilter.CONTOUR)
    image.save("edges.png")
    width, height = image.size

    def findNeighbour(x, y, neighbourRange):
        neighbours = []
        for dx in range(-neighbourRange, neighbourRange + 1):
            for dy in range(-neighbourRange, neighbourRange + 1):
                try:
                    pixeln = image.getpixel((x + dx, y + dy))
                except:
                    pixeln = 255
                if pixeln < threshold:
                    neighbours.append((x + dx, y + dy))
        if len(neighbours) > 0:
            neighbours.sort(key = lambda n: abs((n[0] - x) + (n[1] - y)))
            return neighbours[0]
        return False

##    def deleteNeighbours(x, y, deleteRange):
##        for dx in range(-deleteRange, deleteRange + 1):
##            for dy in range(-deleteRange, deleteRange + 1):
##                try:
##                    image.putpixel((x + dx, y + dy), 255)
##                except:
##                    pass

    def smoothLine(line, factor = 1):
        for k in range(factor - 1):
            for i in range(1, len(line) - 1):
                line[i] = ((line[i-1][0] + line[i+1][0]) / 2, (line[i-1][1] + line[i+1][1]) / 2)
        return line

    lines = []
    currentLine = []
    for x in range(width):
        for y in range(height):
            pixel = image.getpixel((x, y))
            if pixel < threshold:
                currentLine.append((x, y))
                image.putpixel((x, y), 255)
                neighbour = findNeighbour(x, y, neighbourRange)
##                deleteNeighbours(x, y, 3)
                while neighbour:
                    currentLine.append((neighbour[0], neighbour[1]))
                    image.putpixel((neighbour[0], neighbour[1]), 255)
                    neighbour = findNeighbour(neighbour[0], neighbour[1], neighbourRange)
##                    if neighbour:
##                        deleteNeighbours(neighbour[0], neighbour[1], 3)
                if lineReduce == -1:
                    lineReduce = floor(log10(width * height) - 3)
                currentLine = currentLine[0::lineReduce]
                currentLine = smoothLine(currentLine, lineSmooth)
                if len(currentLine) > minimumLine:
                    lines.append(currentLine)
                currentLine = []

    return lines