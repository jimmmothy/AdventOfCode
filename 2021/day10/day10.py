#/usr/bin/python3

import sys

class navigationss:
    def __init__(self):
        self.corrupted = False
        self.illegal = []
        self.totalpoints = []

    def feedLine(self, input):

        left = []
        right = []
        self.corrupted = False
        for x in input:

            if x == "(" or x == "[" or x == "{" or x == "<":
                left.append(x)
                
            elif x == ")" or x == "]" or x == "}" or x == ">":
                right.append(x)

                lbuff = left[len(left)-1]
                rbuff = right[len(right)-1]

                if rbuff == self.expect(lbuff):
                    left.pop()
                    right.pop()


                if rbuff != self.expect(lbuff):
                    self.corrupted = True
                    self.illegal.append(rbuff)
                    break
                
        if self.corrupted == False:
            solution = ""
            for x in reversed(left):
                solution += self.expect(x)
                
            self.totalpoints.append(int(self.findcmp(solution)))


    def expect(self, x) -> chr:
        if x == "<":
            return ">"
        if x == "(":
            return ")"
        if x == "[":
            return "]"
        if x == "{":
            return "}"

    def findScore(self) -> int:

        score = 0
        for x in self.illegal:
            if x == ")":
                score += 3
            elif x == "]":
                score += 57
            elif x == "}":
                score += 1197
            elif x == ">":
                score += 25137
        return score
    
    def findcmp(self, input) -> int:

        score = 0
        for x in input:

            score = score * 5
            if x == ")":
                score += 1
            elif x == "]":
                score += 2
            elif x == "}":
                score += 3
            elif x == ">":
                score += 4
        
        return score
    
    def midScore(self) -> int:

        tmp = sorted(self.totalpoints)
        ind = int((len(self.totalpoints)-1) / 2)
        return tmp[ind]
        
def main():

    input = open(str(sys.argv[1]), "r")
    data = input.readlines()
    
    cake = navigationss()
    for x in data:
        cake.feedLine(x.rstrip())

    # Part one
    print(cake.findScore())

    # Part two
    print(cake.midScore())

if __name__ == '__main__':
    main()