#!/usr/bin/python3

import sys

class rucklist:
    def __init__(self, input: str):
        self.input = input.split('\n')
        self.prio = {}
        self.dayOneTally = 0
        self.dayTwoTally = 0

        self.buildPrioDict()

        self.dayOne()
        self.dayTwo()


    def buildPrioDict(self):
        prio = {}
        for x in range(1, 26+1):
            prio[chr(96 + x)] = x
        for x in range(1, 26+1):
            prio[chr(64 + x)] = x + 26
        self.prio = prio


    def compareRucks(self, ruckA: str, ruckB: str) -> str:
        LA = list(ruckA)
        LB = list(ruckB)
        for x in LA:
            if x in LB:
                return x
        print("Something went wrong comparing")


    def dayOne(self):
        for x in self.input:
            aSide = x[0:len(x)//2]
            bSide = x[len(x)//2 if len(x)%2 == 0 else ((len(x)//2)+1):]
            self.dayOneTally += self.prio[self.compareRucks(aSide, bSide)]
        print(self.dayOneTally)


    def dayTwo(self):
        groups = int(len(self.input) / 3)
        gbuff = 0
        for q in range(0, groups):
            aSide = self.input[gbuff]
            bSide = self.input[gbuff + 1]
            cSide = self.input[gbuff + 2]
            gbuff += 3
            self.dayTwoTally += self.prio[self.compareRucksTres(aSide, bSide, cSide)]
        print(self.dayTwoTally)

    def compareRucksTres(self, ruckA: str, ruckB: str, ruckC: str) -> str:

        LA = list(ruckA)
        LB = list(ruckB)
        LC = list(ruckC)
        for x in LA:
            if x in LB:
                if x in LC:
                    return x
        print("Something went wrong comparing")


def main():

    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = rucklist(rd)

if __name__ == '__main__':
    main()