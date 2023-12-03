import sys


class number:
    def __init__(self, ypos: int, xpos: int, value):
        self.ypos = ypos
        self.xpos = xpos
        self.value = value
        #self.length = len(str(self.value))
        self.transformedValue = 0

class fancyGear:
    def __init__(self, xpos: int, ypos: int):
        self.xpos = xpos
        self.ypos = ypos

        self.adjacentcount = 0
        self.numbers = []

class gearbot:
    def __init__(self, input: str):
        self.input = input
        self.grid = [q[:] for q in input.split('\n')]

        self.gridylim = len(self.grid)
        self.gridxlim = len(self.grid[0])

        self.numbers = []
        self.fancyGears = []
        self.sumOfParts = 0
        self.findNums()
        
        ## day 1
        for q in self.numbers:
            symb = False

            for w in range(0, len(str(q.value))):
                if self.nextToSymbol(q.xpos+w, q.ypos) == True:
                    symb = True

            if symb == True:
                self.sumOfParts += q.value
        print(self.sumOfParts)

        ## day 2
        for q in self.fancyGears:
            self.fancyGearNeedful(q)
        
        gearRatio = 0
        for q in self.fancyGears:
            gearRatio += self.transformNumbers(q)
        print(gearRatio)
    

    def transformNumbers(self, gear: fancyGear) -> int:

        if gear.adjacentcount == 2:

            values = []

            for q in gear.numbers:
                for w in self.numbers:
                    if q[0] == w.xpos and q[1] == w.ypos:
                        values.append(w.value)
            
            return values[0] * values[1]
        return 0
    

    def fancyGearNeedful(self, gear: fancyGear):

        xd = [0, -1, -1, -1, 0, 1, 1, 1]
        yd = [-1, -1, 0, 1, 1, 1, 0, -1]

        for q in range(0, 8):

            x = gear.xpos + xd[q]
            y = gear.ypos + yd[q]

            if self.oobCheck(x, y) == True:

                for w in self.numbers:

                    found = False
                    for l in range(0, len(str(w.value))):
                        if w.xpos + l == x and w.ypos == y:
                            found = True

                    if found == True:
                        numbertup = (w.xpos, w.ypos)
                        if numbertup not in gear.numbers:
                            gear.adjacentcount += 1
                            gear.numbers.append(numbertup)
        

    def oobCheck(self, x: int, y: int) -> bool:

        if y < 0 or x < 0 or y >= self.gridylim or x >= self.gridxlim:
            return False
        else:
            return True


    def nextToSymbol(self, xpos: int, ypos: int) -> bool:

        xd = [0, -1, -1, -1, 0, 1, 1, 1]
        yd = [-1, -1, 0, 1, 1, 1, 0, -1]

        for q in range(0, 8):
            x = xpos + xd[q]
            y = ypos + yd[q]

            if self.oobCheck(x, y) == True:
                curr = self.grid[y][x]

                if curr == '*':
                    ## check fancy gear doesn't already exist
                    exists = False
                    if len(self.fancyGears) > 0:
                        for q in self.fancyGears:
                            if q.xpos == x and q.ypos == y:
                                exists = True

                    if exists == False:
                        self.fancyGears.append(fancyGear(x, y))

                if curr.isdigit() == False and curr != '.':
                    return True                
        return False


    
    def findNums(self):

        y, x = 0, 0
        y_lim = len(self.grid)
        x_lim = len(self.grid[0])

        while y < y_lim:

            x = 0
            numbuff = ""
            xn, yn = x, y

            while x < x_lim:

                current = self.grid[y][x]
                if current.isdigit():
                    numbuff += current

                    if len(numbuff) == 1:
                        xn = x
                    
                else:
                    if len(numbuff) > 0:
                        self.numbers.append(number(yn, xn, int(numbuff)))
                        numbuff = ""
                
                if x == x_lim-1:
                    if len(numbuff) > 0:
                        self.numbers.append(number(yn, xn, int(numbuff)))
                        numbuff = ""
                
                x += 1
            y += 1

        


def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = gearbot(rd)

if __name__ == '__main__':
    main()