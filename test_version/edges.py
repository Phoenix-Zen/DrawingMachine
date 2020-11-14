from PIL import Image, ImageFilter
from math import acos, pi

def findEdges(imageFile, threshold = 10, deleteRange = 3, neighbourRange = 5, lineReduce = 1, lineSmooth = 2):
    image = Image.open(imageFile).convert("L").filter(ImageFilter.FIND_EDGES)
    image.save("edges.png")
    width, height = image.size

    def findNeighbour(x, y, neighbourRange):
        neighbours = []
        for dx in range(-neighbourRange, neighbourRange + 1):
            for dy in range(-neighbourRange, neighbourRange + 1):
                try:
                    pixeln = image.getpixel((x + dx, y + dy))
                except:
                    pixeln = 0
                if pixeln > threshold:
                    neighbours.append((x + dx, y + dy))
        if len(neighbours) > 0:
            neighbours.sort(key = lambda n: abs((n[0] - x) * (n[1] - y)))
            return neighbours[0]
        return False
    
    def deleteNeighbours(x, y, deleteRange):
        for dx in range(-deleteRange, deleteRange + 1):
            for dy in range(-deleteRange, deleteRange + 1):
                try:
                    image.putpixel((x + dx, y + dy), 0)
                except:
                    pass
    
    def reduceLine(line, factor = 2):
        newLine = []
        for i in range(0, len(line), factor):
            newLine.append(line[i])
        return newLine
    
    lines = []
    currentLine = []
    for x in range(width):
        for y in range(height):
            pixel = image.getpixel((x, y))
            if pixel > threshold:
                currentLine.append((x, y))
                image.putpixel((x, y), 0) 
                neighbour = findNeighbour(x, y, neighbourRange)
                deleteNeighbours(x, y, deleteRange)
                while neighbour:
                    currentLine.append((neighbour[0], neighbour[1]))
                    image.putpixel((neighbour[0], neighbour[1]), 0)
                    neighbour = findNeighbour(neighbour[0], neighbour[1], neighbourRange)
                    if neighbour:
                        deleteNeighbours(neighbour[0], neighbour[1], deleteRange)
                currentLine = reduceLine(currentLine, lineReduce)
                lines.append(currentLine)
                currentLine = []

    return lines