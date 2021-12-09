#/usr/bin/python3

import sys

class display:
    def __init__(self):
        self.left = []
        self.right = []

        self.easyCount = 0
        self.hardCount = 0
    
    def parseInput(self, input, partTwo):

        self.input = input
        self.sides = input.split(" | ")

        self.left = self.sides[0]
        self.right = self.sides[1]

        found = 0
        for q in self.right.split(" "):
            length = len(q.rstrip())
            
            
            if length == 2 or length == 4 or length == 3 or length == 7:
                found += 1

        self.easyCount += found
        self.word = ""

        if partTwo == True:

            decoded = [[]] * 10
            coded = []
            for q in self.left.split(" "):

                if len(q) == 2:
                    decoded[1] = [q, 1]
                elif len(q) == 3:
                    decoded[7] = [q, 7]
                elif len(q) == 4:
                    decoded[4] = [q, 4]
                elif len(q) == 7:
                    decoded[8] = [q, 8]
                else:
                    coded.append(q)

            while len(coded) > 0:

                newcoded = []
                for q in coded:
                    clen = len(q)
                    
                    if clen == 6:
                        # find 0
                        if decoded[0] == []:
                            if self.match(q, decoded[4][0]) == 3:
                                if self.match(q, decoded[1][0]) == 2:
                                    decoded[0] = [q, 0]
                            
                        # find 9
                        elif decoded[9] == [] and decoded[6] == []:
                            if self.match(q, decoded[8][0]) == 6:
                                if self.match(q, decoded[7][0]) == 3:
                                    decoded[9] = [q, 9]

                        # find 6
                        elif decoded[6] == []:
                            decoded[6] = [q, 6]
                        
                    elif clen == 5:
                        # find 3
                        if decoded[3] == []:
                            if self.match(q, decoded[1][0]) == 2:
                                decoded[3] = [q, 3]
                        
                        # find 5
                        elif decoded[6] != [] and decoded[5] == []:
                            if self.match(q, decoded[6][0]) == 5:
                                decoded[5] = [q, 5]
                        
                        # find 2
                        elif decoded[2] == []:
                            if decoded[5] != []:
                                decoded[2] = [q, 2]
                    
                    if self.newCoded(decoded, q) == False:
                        newcoded.append(q)

                coded = newcoded

            for q in self.right.rstrip().split(" "):
                for x in decoded:
                    if self.anagram(x[0], q) == True:
                        self.word += str(x[1])
            
            #print(self.word)
            self.hardCount += int(self.word, 10)
    
    def newCoded(self, list, string):
        found = False
        for q in list:
            if q != []:
                if q[0] == string:
                    found = True
        return found

    def anagram(self, inputone, inputtwo):
        if sorted(inputone) == sorted(inputtwo):
            return True
        else:
            return False

    
    def match(self, inputone, inputtwo):
        totalMatches = 0
        for q in inputone:
            for w in inputtwo:
                if q == w:
                    totalMatches += 1
       
        return totalMatches


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
        skynet.parseInput(x, True)

    # Part one
    print(skynet.easyCount)

    # Part two
    print(skynet.hardCount)  
    

if __name__ == '__main__':
    main()