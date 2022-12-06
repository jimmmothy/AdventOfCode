#!/usr/bin/python3

import sys
from time import perf_counter

class giant_cargo_crane:
    def __init__(self, input: str):
        self.input = input.split('\n\n')
        self.stack = {}
        self.numberStacks = 0
        self.maxStackHeight = 0
        
        self.parseInput()
        self.dayOne()
        self.dayTwo()

    def parseInput(self):
        self.input_stack = self.input[0].split('\n')
        self.input_moves = self.input[1].split('\n')
        
        ''' STACK portion of input
        '''
        self.maxStackHeight = len(self.input_stack)-1
        self.numberStacks = int(self.input_stack[self.maxStackHeight][len(self.input_stack[self.maxStackHeight])-2:-1])
        index = 1
        for q in range(1, self.numberStacks+1):
            
            if q != 1:
                index = 1+(4*(q-1))

            self.stack[q] = []
            for z in range(0, self.maxStackHeight):

                target = self.input_stack[z][index]
                if target != ' ':
                    self.stack[q].append(target)
            
            self.stack[q].reverse()
        
    
    def performMove(self, amount: int, origin: int, destination: int, day: int):
        
        if day == 1:
            try:
                for q in range(0, amount):
                    tmp = self.stack[origin].pop()
                    self.stack[destination].append(tmp)
            except:
                print("Something went wrong with stacks")
                return -1
        
        elif day == 2:
            buff = ""
            for q in range(0, amount):
                buff += self.stack[origin].pop()
                
            if len(buff) == 1:
                self.stack[destination].append(buff)
            else:
                buff = reversed(buff)
                for z in buff:
                    self.stack[destination].append(z)

    
    def processMove(self, input: str, day: int):
        rawD = input.split( ' ')
        amount = int(rawD[1])
        origin = int(rawD[3])
        destination = int(rawD[5])
        self.performMove(amount, origin, destination, day)
    
    def findTopStr(self):
        answer = ""
        ringer_dict = self.stack.copy()

        for q in range(1, self.numberStacks+1):
            if len(ringer_dict[q]) == 0:
                continue
            else:
                answer += ringer_dict[q].pop()
        print(answer)
                

    def dayOne(self):
        for q in self.input_moves:
            self.processMove(q,1)
        self.findTopStr()

    def dayTwo(self):
        self.parseInput()
        for q in self.input_moves:
            self.processMove(q,2)
        self.findTopStr()
        

def main():

    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong with input file")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = giant_cargo_crane(rd)

if __name__ == '__main__':
    main()