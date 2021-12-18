#/usr/bin/python3

import sys

class navpoint:
    def __init__(self, input):
        self.name = input
        self.start = False
        self.end = False
        self.big = False

        if self.name == "start":
            self.start = True
        else:
            self.start = False

        if self.name == "end":
            self.end = True
        else:
            self.end = False
            
        
        if input.isupper() == True:
            self.big = True
        else:
            self.big = False

        self.connections = []

    def addConnection(self, name):

        found = False
        for x in self.connections:
            if x == name:
                found = True
        
        if found == False:
            self.connections.append(name)

class navsystem:
    def __init__(self):
        self.pointlist = []
        self.navPaths = []
        self.total = 0

    def findPoint(self, name):

        for x in self.pointlist:
            if x.name == name:
                return x

    def genPath(self, parttwo: bool):

        self.part = parttwo
        self.navPaths = []
        self.total = 0
        self.generate("start", self.genChoices("start"))

        print(len(self.navPaths))
                
    
    def genChoices(self, name):

        target = self.findPoint(name)
        return target.connections


    def generate(self, existing, choices):

        for x in choices:
            tmp = existing

            if x == "end":
                tmp += "," + x
                self.navPaths.append(tmp)

            else:
                tmp += "," + x
                if self.checkLegal(tmp) == True:
                    self.generate(tmp, self.genChoices(x))


    def checkLegal(self, existing: str) -> bool:

        startcount = 0
        smalldouble = False
        smalltriple = False
        smalllist = []

        if self.part == False:
            for x in existing.split(","):
                if x.isupper() == False:
                    if x not in smalllist:
                        smalllist.append(x)
                    else:
                        smalldouble = True
                if x == "start":
                    startcount += 1

            if smalldouble == True or startcount > 1:
                return False
            else:
                return True

        else:
            for x in existing.split(","):
                if x.isupper() == False:

                    found = False
                    for y in smalllist:
                        if y == x:
                            found = True
                            if smalldouble == True:
                                smalltriple = True
                            else:
                                smalldouble = True

                    if found == False:
                        smalllist.append(x)

                if x == "start":
                    startcount += 1

            if smalltriple == True or startcount > 1:
                return False
            else:
                return True

    
    def doesItExist(self, name):

        found = False
        for x in self.pointlist:
            if x.name == name:
                found = True
        return found

    def parseInput(self, fro, to):

        if self.doesItExist(fro) == False:
            tmp = navpoint(fro)
            tmp.addConnection(to)
            self.pointlist.append(tmp)
        else:
            for x in self.pointlist:
                if x.name == fro:
                    x.addConnection(to)

        if self.doesItExist(to) == False:
            tmp = navpoint(to)
            tmp.addConnection(fro)
            self.pointlist.append(tmp)
        else:
            for x in self.pointlist:
                if x.name == to:
                    x.addConnection(fro)
        

def main():

    input = [x.rstrip() for x in open(str(sys.argv[1]), "r").readlines()]

    skynet = navsystem()
    for x in input:
        skynet.parseInput(x.split("-")[0], x.split("-")[1])
    
    # Part one
    skynet.genPath(False)

    # Part two
    skynet.genPath(True)
    

if __name__ == '__main__':
    main()