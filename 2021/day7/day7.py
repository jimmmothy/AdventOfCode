#/usr/bin/python3

import sys

class crab:
    def __init__(self, input):
        self.total_crabbies = [int(x) for x in input.split(",")]

        self.lowest = self.total_crabbies[0]
        self.highest = 0
        for x in self.total_crabbies:
            if x < self.lowest:
                self.lowest = x
            elif x > self.highest:
                self.highest = x

    def checkZone(self, zone, partTwo):

        fuel = 0

        if partTwo == False:
            for x in self.total_crabbies:
                if x != zone:
                    
                    dz = abs(x - zone)
                    fuel += dz

        else:
            for x in self.total_crabbies:
                if x != zone:
                    
                    dz = self.checkFuel(abs(x - zone))
                    fuel += dz

        return fuel

    def checkFuel(self, number):

        count = 0
        for x in range(0, number + 1):
            count += x
        return count

    def checkAllZones(self, partTwo):

        lowestzone = 0
        lowestnumber = self.checkZone(1, partTwo)
        
        for x in range(self.lowest, self.highest + 1):
            currentf = self.checkZone(x, partTwo)

            if currentf < lowestnumber:
                
                lowestzone = x
                lowestnumber = currentf
        
        print(f"{lowestnumber}")


def main():

    input = open(str(sys.argv[1]), "r")
    rawinput = input.read()
    rawinput = rawinput.rstrip()

    # Part one
    crabs = crab(rawinput)
    crabs.checkAllZones(False)
    
    # Part two
    crabs.checkAllZones(True)

if __name__ == '__main__':
    main()