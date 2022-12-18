#!/usr/bin/python3

import sys


class ropeb:
    def __init__(self, input: str):
        self.input = [z.split(' ') for z in input.rstrip().split('\n')]
        
        # day 1
        self.tailLocations = [(0,0)]
        self.snakex = [0,0,0,0,0,0,0,0,0,0]
        self.snakey = [0,0,0,0,0,0,0,0,0,0]
        self.ropeybridge(1)

        # day 2 (reset)
        self.tailLocations = [(0,0)]
        self.snakex = [0,0,0,0,0,0,0,0,0,0]
        self.snakey = [0,0,0,0,0,0,0,0,0,0]
        self.ropeybridge(9)


    def ropeybridge(self, limit: int) -> None:
        for q,w in self.input:
            direction = q
            for e in range(0, int(w)):
                if direction == "U":
                    self.snakey[0] += 1
                elif direction == "D":
                    self.snakey[0] -= 1
                elif direction == "L":
                    self.snakex[0] -= 1
                elif direction == "R":
                    self.snakex[0] += 1

                # move tails
                for a in range(1, limit+1):
                    if self.touchingTips(a) == False:
                        self.moveTail(a)

                if tuple((self.snakex[limit], self.snakey[limit])) not in self.tailLocations:
                    self.tailLocations.append(tuple((self.snakex[limit], self.snakey[limit])))
        # answer
        print(f"{len(self.tailLocations)}")
    

    def moveTail(self, index: int) -> None:
        # up/down/left/right
        if self.ady == 0 or self.adx == 0:
            if self.dy > 1:
                self.snakey[index] += 1
            elif self.dy < -1:
                self.snakey[index] -= 1
        
            if self.dx > 1:
                self.snakex[index] += 1
            elif self.dx < -1:
                self.snakex[index] -= 1
        
        # diagonal
        elif self.ady == 2 and self.adx == 1:
            if self.dx == 1:
                self.snakex[index] += 1
            elif self.dx == -1:
                self.snakex[index] -= 1
            
            if self.dy == 2:
                self.snakey[index] += 1
            elif self.dy == -2:
                self.snakey[index] -= 1
        
        elif self.ady == 1 and self.adx == 2:
            if self.dx == 2:
                self.snakex[index] += 1
            elif self.dx == -2:
                self.snakex[index] -= 1
            
            if self.dy == 1:
                self.snakey[index] += 1
            elif self.dy == -1:
                self.snakey[index] -= 1

        elif self.ady == 2 and self.adx == 2:
            if self.dx == 2:
                self.snakex[index] += 1
            elif self.dx == -2:
                self.snakex[index] -= 1
            
            if self.dy == 2:
                self.snakey[index] += 1
            elif self.dy == -2:
                self.snakey[index] -= 1


    def touchingTips(self, index: int) -> bool:
        self.dx = self.snakex[index-1] - self.snakex[index]
        self.dy = self.snakey[index-1] - self.snakey[index]

        self.adx = abs(self.dx)
        self.ady = abs(self.dy)

        # on top
        if self.adx == 0 and self.ady == 0:
            return True
        
        # adjacent left/right
        if self.snakey[index-1] == self.snakey[index]:
            if self.adx <= 1:
                return True
        # adjacent up/down
        if self.snakex[index-1] == self.snakex[index]:
            if self.ady <= 1:
                return True
        
        # diagonal
        if self.ady <=1 and self.adx <= 1:
            return True

        return False

        
def main():
    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong with input file")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = ropeb(rd)

if __name__ == '__main__':
    main()