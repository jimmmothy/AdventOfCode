#/usr/bin/python3

import sys
import numpy as np
import re

class vents:
    def __init__(self, width, height):
        self.board = np.zeros((width, height))

    def drawLine(self, x1, y1, x2, y2, partTwo):
        dx = abs(x2 - x1)
        dy = abs(y2 - y1)

        # vert
        if x1 == x2:
            if y1 < y2:
                for q in range(0,dy+1):
                    self.board[x1, y1 + q] += 1
            else:
                for q in range(0,dy+1):
                    self.board[x1, y1 - q] += 1

        # hori
        elif y1 == y2:
            if x1 < x2:
                for q in range(0, dx+1):
                    self.board[x1 + q, y1] += 1
            else:
                for q in range(0, dx+1):
                    self.board[x1 - q, y1] += 1
        
        # diag
        elif partTwo == True:
            for q in range(0, dx + 1):
                if x1 < x2:
                    xx = x1 + q
                else:
                    xx = x1 - q
                
                if y1 < y2:
                    yy = y1 + q
                else:
                    yy = y1 - q
            
                self.board[xx,yy] += 1

    def countMin(self, min):
        count = 0
        for x,y in enumerate(self.board):
            for q in y:
                if q >= min:
                    count += 1
        return count

def parseInput(sinput):
    x1 = sinput.split(" -> ")[0].split(",")[0]
    y1 = sinput.split(" -> ")[0].split(",")[1]

    x2 = sinput.split(" -> ")[1].split(",")[0]
    y2 = sinput.split(" -> ")[1].split(",")[1]

    return int(x1), int(y1), int(x2), int(y2)

def main():

    input = open(str(sys.argv[1]), "r")
    rawinput = input.read().splitlines()

    # Part one
    thevent = vents(999,999)
    for q in rawinput:
        x1, y1, x2, y2 = parseInput(q)
        thevent.drawLine(x1, y1, x2, y2, False)
    print(thevent.countMin(2))

    # Part two
    thevent = vents(999,999)
    for q in rawinput:
        x1, y1, x2, y2 = parseInput(q)
        thevent.drawLine(x1, y1, x2, y2, True)
    print(thevent.countMin(2))


if __name__ == '__main__':
    main()