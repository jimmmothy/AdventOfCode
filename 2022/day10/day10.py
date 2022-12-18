#!/usr/bin/python3

import sys
import math

class cpu:
    def __init__(self):
        self.x = 1
        self.cycles = 0
        self.signallist = []
        self.tube = ""
    

    def printtube(self) -> None:
        count = 0
        for _ in range(0, 6):
            print((self.tube[count:count+40]))
            count += 40
    

    def sumofstr(self) -> int:
        tmp = 0
        for q in self.signallist:
            tmp += q
        return tmp
    

    def inccycles(self, amount: int) -> None:
        for _ in range(0, amount):
            # day 2 logic
            layer = math.trunc(self.cycles / 40)
            offset = self.cycles - (layer * 40)
            
            if offset == self.x or offset == self.x-1 or offset == self.x+1:
                self.tube += "#"
            else:
                self.tube += "."
            self.cycles += 1

            # day 1 logic
            if self.cycles <= 220:
                if self.cycles == 20 or (self.cycles-20) % 40 == 0:
                    self.signallist.append(self.x * self.cycles)


    def addx(self, op: int) -> None:
        self.inccycles(2)
        self.x += op
        
    def noop(self) -> None:
        self.inccycles(1)
    

    def sendopcode(self, opcode: str) -> None:
        sopc = opcode.split(' ')
        if len(sopc) == 1:

            if opcode == "noop":
                self.noop()
        
        elif len(sopc) == 2:
            opc = sopc[0]
            arg = int(sopc[1])

            if opc == "addx":
                self.addx(arg)

def main():
    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong with input file")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    

    input = [z for z in rd.split('\n')]
    intelceleron = cpu()

    for q in input:
        intelceleron.sendopcode(q)
    
    # day 1
    print(intelceleron.sumofstr())
    # day 2
    intelceleron.printtube()

if __name__ == '__main__':
    main()