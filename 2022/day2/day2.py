#!/usr/bin/python3

import sys

class tourney:
    def __init__(self, input: str):
        self.input = input.split('\n')
        self.totalScore = 0

        self.scoreLost = 0
        self.scoreDraw = 3
        self.scoreWon = 6

        self.dayOne()
        self.dayTwo()

    def dayOne(self):
        for x in self.input:
            opponentMove = x.split(' ')[0]
            myMove = x.split(' ')[1]
            self.totalScore += self.getScore(opponentMove, myMove)
        print(self.totalScore)


    def dayTwo(self):
        for x in self.input:
            opponentMove = x.split(' ')[0]
            reqOutcome = x.split(' ')[1]
            myMove = self.findMove(opponentMove, reqOutcome)
            self.totalScore += self.getScore(opponentMove, myMove)
        print(self.totalScore)

    def findMove(self, oMove: str, reqOutcome: str) -> str:

        '''
        rMove- X Lose / Y Draw / Z Win
        oMove- A Rock / B Paper / C Scissors
        mMove- X Rock / Y Paper / Z Scissors
        '''

        # lose
        if reqOutcome == 'X':
            if oMove == 'A':
                return 'Z'
            elif oMove == 'B':
                return 'X'
            elif oMove == 'C':
                return 'Y'
        
        # draw
        elif reqOutcome == 'Y':
            if oMove == 'A':
                return 'X'
            elif oMove == 'B':
                return 'Y'
            elif oMove == 'C':
                return 'Z'
        
        # win
        elif reqOutcome == 'Z':
            if oMove == 'A':
                return 'Y'
            elif oMove == 'B':
                return 'Z'
            elif oMove == 'C':
                return 'X'


    def getScore(self, oMove: str, mMove: str) -> int:
        if oMove == mMove:
            return 3
        
        mShape = 0
        if mMove == 'X':
            mShape = 1
        elif mMove == 'Y':
            mShape = 2
        elif mMove == 'Z':
            mShape = 3

        # win
        if oMove == 'A' and mMove == 'Y' or \
            oMove == 'B' and mMove == 'Z' or \
            oMove == 'C' and mMove == 'X':
            return mShape + self.scoreWon
        # draw
        elif oMove == 'A' and mMove == 'X' or \
            oMove == 'B' and mMove == 'Y' or \
            oMove == 'C' and mMove == 'Z':
            return mShape + self.scoreDraw
        # lose
        else:
            return mShape + self.scoreLost



def main():

    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = tourney(rd)

if __name__ == '__main__':
    main()