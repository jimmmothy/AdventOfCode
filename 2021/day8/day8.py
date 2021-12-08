#/usr/bin/python3

import sys

class display:
    def __init__(self):
        self.left = []
        self.right = []

        self.easyCount = 0
    
    def parseInput(self, input, partTwo):

        self.input = input
        self.sides = input.split(" | ")
        #print(self.sides)

        self.left = self.sides[0]
        self.right = self.sides[1]

        found = 0
        for q in self.right.split(" "):
            length = len(q.rstrip())
            
            
            if length == 2 or length == 4 or length == 3 or length == 7:
                found += 1

        self.easyCount += found

        #if partTwo == True:

    def anagram(self, inputone, inputtwo):
        if sorted(inputone) == sorted(inputtwo):
            return True
        else:
            return False


    def addOutput(self):
        rightSide = self.sides[1].split(" ")
        self.totalOutput = len(rightSide)
        for x in rightSide:
            self.outputs.append(x)



def main():

    input = open(str(sys.argv[1]).rstrip(), "r")
    rawinput = input.readlines()

    skynet = display()
    for x in rawinput:
        skynet.parseInput(x, False)
        #print(skynet.input)

    # Part one
    print(skynet.easyCount)

    # Part two


    
    
    

if __name__ == '__main__':
    main()