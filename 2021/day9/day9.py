#/usr/bin/python3

import sys
import numpy as np

class cavefloor:
    def __init__(self, input):

        self.map = np.array(input)
        self.iwid = self.map.shape[1]
        self.ihei = self.map.shape[0]
        self.lowPoints = []
    
    def countLowPoints(self):
        risk = 1
        sum = 0
        for x in self.lowPoints:
            if x != []:
                sum += x[1] + risk
        return sum

    def lowestPoint(self):

        for y in range(0, self.ihei):
            for x in range(0, self.iwid):

                cpoint = self.map[y][x]
                if self.checkNumber(y, x, cpoint) != True:
                    self.lowPoints.append([(y, x), cpoint])
    
    def countBasins(self):

        basincount = []
        for q in self.lowPoints:

            y = q[0][0]
            x = q[0][1]

            currentBasin = []
            currentBasin.append(q[0])

            excluded = []
            count, excluded = self.buildBasin(x, y, excluded)
            basincount.append(count+1)
        print(self.sumBasins(basincount))


    def sumBasins(self, basins) -> int:

        basins = sorted(basins)
        basins.reverse()
        return (basins[0] * basins[1] * basins[2])
    
    def buildBasin(self, x: int, y: int, excluded: list):

        if tuple((x, y)) not in excluded:
            excluded.append(tuple((x, y)))

        count = 0
        n, s, e, w = self.nsew(x, y)
        
        if n == True:
            if self.checkNine(x, y-1, 9) == False and tuple((x, y-1)) not in excluded:
                count += 1
                tmpcount, excluded = self.buildBasin(x, y-1, excluded)
                count += tmpcount
        if s == True:
            if self.checkNine(x, y+1, 9) == False and tuple((x, y+1)) not in excluded:
                count += 1
                tmpcount, excluded = self.buildBasin(x, y+1, excluded)
                count += tmpcount
        if e == True:
            if self.checkNine(x+1, y, 9) == False and tuple((x+1, y)) not in excluded:
                count += 1
                tmpcount, excluded = self.buildBasin(x+1, y, excluded)
                count += tmpcount
        if w == True:
            if self.checkNine(x-1, y, 9) == False and tuple((x-1, y)) not in excluded:
                count += 1
                tmpcount, excluded = self.buildBasin(x-1, y, excluded)
                count += tmpcount
        
        return count, excluded


    def checkNine(self, x: int, y: int, z: int) -> bool:
            
        if x >= self.iwid or x < 0 or y >= self.ihei or y < 0:
            return False

        if self.map[y][x] == z:
            return True
        else:
            return False

        
    
    def nsew(self, x: int, y: int) -> bool:

        north = True
        east = True
        south = True
        west = True

        if y == 0:
            north = False
        elif y == self.ihei - 1:
            south = False
        if x == 0:
            west = False
        elif x == self.iwid - 1:
            east = False
        
        return north, south, east, west

    def checkNumber(self, y: int, x: int, z: int) -> bool:
            
        north, south, east, west = self.nsew(x, y)
        foundLower = False

        if north == True:
            if self.map[y-1][x] <= z:
                foundLower = True
        
        if south == True:
            if self.map[y+1][x] <= z:
                foundLower = True
        
        if east == True:
            if self.map[y][x+1] <= z:
                foundLower = True

        if west == True:
            if self.map[y][x-1] <= z:
                foundLower = True
        
        return foundLower

def main():

    data = []
    for q in open(str(sys.argv[1]), "r").readlines():
        line = []
        for w in q.rstrip():
            line.append(int(w))
        data.append(line)
    
  
    # Part one
    lavamap = cavefloor(data)
    lavamap.lowestPoint()
    print(lavamap.countLowPoints())
    
    # Part two
    lavamap.countBasins()

if __name__ == '__main__':
    main()
