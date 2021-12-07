#/usr/bin/python3

import sys

class fishies:
    def __init__(self, school):
        total_fishies = len(school.split(","))
        self.school = [int(x) for x in school.split(",")]
        self.count = [0] * 9

        for q,w in enumerate(self.school):
            self.count[w] += 1
    
    def countFish(self):
        count = 0
        for x in self.count:
            count += x
        return count
    
    def progressDays(self, days):
        for q in range(0, days):
            self.progressDay()

    def progressDay(self):
        newFish = 0
        newCount = [0] * 9

        for q in range(0, 9):
            if q == 0:
                newCount[6] = self.count[0]
                newCount[8] += self.count[0]
            elif q == 7:
                newCount[6] += self.count[7]
            else:
                newCount[q - 1] = self.count[q]

        self.count = newCount

def main():

    input = open(str(sys.argv[1]), "r")
    rawinput = input.read()
    rawinput = rawinput.rstrip()

    # Part one
    lanterns = fishies(rawinput)
    lanterns.progressDays(80)
    print(lanterns.countFish())

    # Part two
    lanterns = fishies(rawinput)
    lanterns.progressDays(256)
    print(lanterns.countFish())


if __name__ == '__main__':
    main()