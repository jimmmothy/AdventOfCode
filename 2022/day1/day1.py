#!/usr/bin/python3

from posixpath import split
import sys

class calorieBot:
    def __init__(self, input: str):
        self.input = input
        self.highScore = 0
        self.buffScore = 0
        self.scoreCount = []
        self.dayTwo()
    
    def checkCount(self):
        if self.buffScore > self.highScore:
            self.highScore = self.buffScore


    def dayOne(self):
        
        for splitData in self.input.split('\n\n'):
            splitFurther = splitData.split('\n')
            inputsHere = len(splitFurther)
            for x in range (0, inputsHere):
                self.buffScore += int(splitFurther[x])
            self.checkCount()
            self.buffScore = 0
        print(self.highScore)

    def dayTwo(self):
        
        for splitData in self.input.split('\n\n'):
            splitFurther = splitData.split('\n')
            inputsHere = len(splitFurther)
            for x in range (0, inputsHere):
                self.buffScore += int(splitFurther[x])
            self.scoreCount.append(self.buffScore)
            self.buffScore = 0

        self.scoreCount.sort(reverse=True)
        topThree = 0
        for x in range(0, 3):
            topThree += int(self.scoreCount[x])
        print(topThree)

def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = calorieBot(rd)

if __name__ == '__main__':
    main()