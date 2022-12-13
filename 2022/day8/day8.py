#!/usr/bin/python3

import sys


class trees:
    def __init__(self, input: str):
        self.input = [z for z in input.rstrip().split('\n')]
        self.width = len(self.input[0])
        self.height = len(self.input)
        self.outside = (self.width * 2) + (self.height * 2) - 4

        self.dayOne()
        self.dayTwo()
    
    def dayTwo(self) -> None:
        # walk whole input
        highscore= 0

        for y in range(0,self.height):
            for x in range(0, self.width):

                counts = []
                score = 1
                counts.append(self.middleOut(x,y,"N"))
                counts.append(self.middleOut(x,y,"S"))
                counts.append(self.middleOut(x,y,"E"))
                counts.append(self.middleOut(x,y,"W"))

                for q in counts:
                        score = score * q

                if score > highscore:
                    highscore = score
        print(highscore)


    def middleOut(self, x:int, y:int, direction: str) -> int:

        if direction == "N" and y == 0 or \
            direction == "S" and y == self.height-1 or \
            direction == "E" and x == self.width-1 or \
            direction == "W" and x == 0:
            return 0
        
        target = self.input[y][x]
        count = 0
        stop = False

        if direction == "N":
            while stop == False:
                y -= 1
                if y == 0:
                    stop = True
                    count += 1
                else:
                    tmpTarget = self.input[y][x]
                    if target > tmpTarget:
                        count += 1
                    else:
                        count += 1
                        stop = True
        elif direction == "S":
            while stop == False:
                y += 1
                if y == self.height-1:
                    stop = True
                    count += 1
                else:
                    tmpTarget = self.input[y][x]
                    if target > tmpTarget:
                        count += 1
                    else:
                        count += 1
                        stop = True
        elif direction == "E":
            while stop == False:
                x += 1
                if x == self.width-1:
                    stop = True
                    count += 1
                else:
                    tmpTarget = self.input[y][x]
                    if target > tmpTarget:
                        count += 1
                    else:
                        count += 1
                        stop = True
        elif direction == "W":
            while stop == False:
                x -= 1
                if x == 0:
                    stop = True
                    count += 1
                else:
                    tmpTarget = self.input[y][x]
                    if target > tmpTarget:
                        count += 1
                    else:
                        count += 1
                        stop = True
        return count


    def dayOne(self) -> None:
        tally = 0
        for q in self.findMids():
            if self.isVisisble(q[0],q[1]) == True:
                tally += 1
        print(tally + self.outside)

    
    def findMids(self) -> list:
        x1 = 1
        x2 = self.width-1
        y1 = 1
        y2 = self.height-1
        listerine = []

        for y in range(y1, y2):
            for x in range(x1, x2):
                listerine.append((x, y))
        return listerine


    def isVisisble(self, x: int, y: int) -> bool:
        targetHeight = int(self.input[y][x])
        visible = True
        N = self.grabComparers(x,y,"N")
        if len(N) != None:
            N.sort(reverse=True)
            if targetHeight <= N[0]:
                visible = False
        if visible == True:
            return True

        visible = True
        S = self.grabComparers(x,y,"S")
        if len(N) != None:
            S.sort(reverse=True)
            if targetHeight <= S[0]:
                visible = False
        if visible == True:
            return True

        visible = True
        E = self.grabComparers(x,y,"E")
        if len(N) != None:
            E.sort(reverse=True)
            if targetHeight <= E[0]:
                visible = False
        if visible == True:
            return True

        visible = True
        W = self.grabComparers(x,y,"W")
        if len(N) != None:
            W.sort(reverse=True)
            if targetHeight <= W[0]:
                visible = False
        if visible == True:
            return True
        else:  
            return False


    def grabComparers(self, x: int, y: int, direction: str) -> list:
        theList = []
        if direction == "N":
            for q in range(0, y):
                theList.append(int(self.input[q][x]))
        elif direction == "S":
            for q in range(y+1, self.height):
                theList.append(int(self.input[q][x]))
        elif direction == "E":
            for q in range(x+1, self.width):
                theList.append(int(self.input[y][q]))
        elif direction == "W":
            for q in range(0, x):
                theList.append(int(self.input[y][q]))
        return theList

        
def main():
    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong with input file")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = trees(rd)

if __name__ == '__main__':
    main()