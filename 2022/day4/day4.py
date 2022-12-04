#!/usr/bin/python3

import sys

class cleaningRoster:
    def __init__(self, input: str):
        self.input = input.split('\n')
        self.edibles = 0
        self.dayTwoCount = 0

        self.dayOne()
        self.dayTwo()
    
    def dayOne(self):
        
        for q in self.input:            
            aSide = self.makeList(q.split(',')[0])
            bSide = self.makeList(q.split(',')[1])

            canary = False
            for x in aSide:
                if x not in bSide:
                    canary = True

            if canary == False:
                self.edibles += 1
            else:
                canary = False
                for x in bSide:
                    if x not in aSide:
                        canary = True
                if canary == False:
                    self.edibles += 1

        print(self.edibles)
    
    def dayTwo(self):
        
        for q in self.input:            
            aSide = self.makeList(q.split(',')[0])
            bSide = self.makeList(q.split(',')[1])

            canary = False
            for x in aSide:
                if x in bSide:
                    canary = True
            if canary == True:
                self.dayTwoCount += 1

        print(self.dayTwoCount)

            

    def makeList(self, incoming: str) -> list:
        start = int(incoming.split('-')[0])
        end = int(incoming.split('-')[1])
        el_list = []
        for q in range(start, end+1):
            el_list.append(q)
        return el_list

def main():

    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = cleaningRoster(rd)

if __name__ == '__main__':
    main()