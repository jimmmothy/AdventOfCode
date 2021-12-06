#/usr/bin/python3

import sys
import numpy as np
import re

class bingo:
    def __init__(self, board, width, height):
        self.board = board
        self.width = width
        self.height = height
        self.hits = np.zeros(self.width * self.height)
        self.alive = True

    def checkNumber(self, number):
        # Look for number on board
        count = 0
        for x in self.board:
            if x == number:
                self.hits[count] = 1
            count += 1
    
    def sumOfUnchecked(self):
        count = 0
        sum = 0
        for x in self.board:
            if self.hits[count] != 1:
                sum += int(x)
            count += 1
        return sum
    
    def checkLines(self):   

        found = True

        # Horizontal
        for y in range(0, self.height):
            found = True
            for x in range(0, self.width):
                if self.hits[(y * self.width) + x] != 1:
                    found = False
            if found == True:
                return True

        # Vertical
        for x in range(0, self.height):
            found = True
            for y in range(0, self.width):
                if self.hits[(y * self.width) + x] != 1:
                    found = False
            if found == True:
                return True

        # Diagonal
        found = True
        for q in range(0, self.width):
            if self.hits[(q * self.width) + q] != 1:
                found = False
        if found == True:
                return True
        
        found = True
        for q in reversed(range(0, self.width)):
            if self.hits[(q * self.width) + q] != 1:
                found = False
        if found == True:
                return True

        return False

def main():

    input = open(str(sys.argv[1]), "r")
    rawinput = ""
    for x in input:
        rawinput += x

    rawinput.rstrip()
    numbers = rawinput.split("\n")[0].split(",")

    width = 5
    height = 5
    players = []

    for x in range(1, len(rawinput.split("\n\n"))):
        full_card = []

        for y in (rawinput.rstrip()).split("\n\n")[x].split("\n"):
            
            regex = "([\d]+)[\s]+([\d]+)[\s]+([\d]+)[\s]+([\d]+)[\s]+([\d]+)"
            reg = re.findall(regex, y)

            for q in reg[0]:
                full_card.append(q)

        players.append(bingo(full_card, width, height))

    # Part one
    round = 0
    winner_found = False

    while winner_found == False:
        x = numbers[round]

        for q in players:
            q.checkNumber(x)
        
        # Look for BINGO
        for q in players:
            winner_found = q.checkLines()

            if winner_found == True:
                answer = (q.sumOfUnchecked() * int(x))
                print(answer)
                break
        
        round += 1
    
    # Part two
    round = 0
    line_found = False
    winner_found = False
    players_left = len(players)

    while winner_found != True:
        x = numbers[round]

        for q in players:
            q.checkNumber(x)
        
        # Look for BINGO
        for q in players:
            if q.alive == False:
                continue

            line_found = q.checkLines()
            
            if line_found == True:
                
                if players_left > 1:
                    q.alive = False
                    players_left -= 1

                elif players_left == 1:
                    answer = (q.sumOfUnchecked() * int(x))
                    print(answer)
                    winner_found = True
                    break
        
        round += 1

if __name__ == '__main__':
    main()