#/usr/bin/python3
 
import sys

class octopus:

    def __init__(self, input: list, wid: int, hei: int) -> None:
        self.wid = wid
        self.hei = hei
        self.total = wid * hei
        self.grid = input
        self.flashing = 0
        self.currentlyFlashing = 0
    
    def anyG9(self) -> bool:

        for y in range(0, self.hei):
            for x in range(0, self.wid):
                if self.grid[y][x] > 9:
                    return True
        return False

    def singleStep(self):

        self.currentlyFlashing = 0

        for y in range(0, self.hei):
            for x in range(0, self.wid):
                
                self.addOne(x, y)

        while (self.anyG9() == True):

            for y in range(0, self.hei):
                for x in range(0, self.wid):

                    for x in range(0, self.wid):
                        oct = self.grid[y][x]

                        if oct > 9:
                            self.flashing += 1
                            self.currentlyFlashing += 1
                            self.grid[y][x] = 0
                            self.addOneAround(x, y, 0)


    def nsew(self, x: int, y: int) -> bool:

        north = True
        east = True
        south = True
        west = True

        if y == 0:
            north = False
        elif y == self.hei - 1:
            south = False
        if x == 0:
            west = False
        elif x == self.wid - 1:
            east = False
        
        return north, south, east, west

    def addOne(self, x: int, y: int) -> None:

        q = self.grid[y][x] + 1
        self.grid[y][x] = q

    def addOneAround(self, x: int, y: int, z: chr) -> None:

        n, s, e, w = self.nsew(x, y)

        if n == True:
            if self.grid[y-1][x] != z:
                self.addOne(x,y-1)
            if w == True:
                if self.grid[y-1][x-1] != z:
                    self.addOne(x-1, y-1)
            if e == True:
                if self.grid[y-1][x+1] != z:
                    self.addOne(x+1,y-1)

        if s == True:
            if self.grid[y+1][x] != z:
                self.addOne(x,y+1)
            if e == True:
                if self.grid[y+1][x+1] != z:
                    self.addOne(x+1,y+1)
            if w == True:
                if self.grid[y+1][x-1] != z:
                    self.addOne(x-1,y+1)
                
        if e == True:
            if self.grid[y][x+1] != z:
                self.addOne(x+1,y)
            
        if w == True:
            if self.grid[y][x-1] != z:
                self.addOne(x-1,y)
    

def main():

    input = open(str(sys.argv[1]), "r")
    data = []
    for x in input.readlines():
        tmp = []
        for y in x[:-1]:
            tmp.append(int(y))
        data.append(tmp)

    width = len(data[0])
    height = len(data)

    octo = octopus(data, width, height)
    count = 0

    # Part one
    while count < 100:
        octo.singleStep()
        count += 1
    print(octo.flashing)

    # Part two
    while octo.currentlyFlashing != octo.total:
        octo.singleStep()
        count += 1
    print(count)


if __name__ == "__main__":
    main()