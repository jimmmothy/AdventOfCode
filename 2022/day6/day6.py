#!/usr/bin/python3

import sys

'''
To fix the communication system, you need to add a subroutine to the device that detects a start-of-packet marker in the datastream.
In the protocol being used by the Elves, the start of a packet is indicated by a sequence of four characters that are all different.
'''
class signald:
    def __init__(self, input: str):
        self.input = input
        # day 1
        self.findTheThings(4)
        # day 2
        self.findTheThings(14)
    
    def findTheThings(self, depth: int):

        pc = depth
        buff = []
        sigview = self.input[:depth]
        collision = False

        for q in range(pc, len(self.input)-depth):
            for w in range(0, depth):
                target = sigview[w]
                
                if target in buff:
                    collision = True
                else:
                    buff.append(target)

            if collision == False:
                break
            else:
                collision = False

            pc += 1
            buff = []
            sigview = self.input[pc-depth:pc+depth]
        print(pc)


def main():

    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong with input file")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = signald(rd)

if __name__ == '__main__':
    main()