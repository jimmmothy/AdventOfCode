#!/usr/bin/python3

import sys


class thisIsAUnixSystemIKnowThis:
    def __init__(self, input: str):
        self.input = input.split('\n')
        self.length = len(self.input)
        
        # set up / directory
        self.cwd = ""
        self.ssd = {}
        self.ssd["/"] = {'name': '/', 'size': 0, 'parent_id': 'root', 'type': 'dir'}
          
        self.parseInput()
        self.findSizes("/",0)

        self.dayOne()
        self.dayTwo()
        

    def buildCwd1Up(self) -> str:
        a = self.cwd[1:].split("/")
        tmp = ""
        for q in range(0, len(a)-1):
            tmp += "/" + a[q]
        return tmp


    def parseInput(self):

        for q in self.input:
            sq = q.split(' ')

            # cd commands            
            if q == "$ cd /":
                self.cwd = "/"

            elif sq[1] == "cd":
                if sq[2] != "..":
                    if self.cwd == "/":
                        self.cwd += sq[2]
                    else:
                        self.cwd += "/" +sq[2]
                else:
                    # rebuilt cwd back 1 layer
                    self.cwd = self.buildCwd1Up()
            
            elif sq[1] != "ls":
                element_size = sq[0]
                element_name = sq[1]
                parent_id = ""

                if self.cwd == "/":
                    parent_id = "/"
                    uuid = self.cwd + element_name
                else:
                    parent_id = self.cwd
                    uuid = self.cwd + "/" + element_name

                # file w/ size and name
                if sq[0].isdigit() == True:
                    self.ssd[uuid] = {'name': element_name, 'size': int(element_size), \
                        'parent_id': parent_id, 'type': 'file'}
                
                # dir w/ name
                else:
                    self.ssd[uuid] = {'name': element_name, 'size': 0, 'parent_id': parent_id, \
                        'type': 'dir'}


    def findSizes(self, startPoint: str, depth: int):

        tmp = '\t' * depth
        # grab a list of all elements that have startPoint as their parent
        currentLevel = []
        for q in self.ssd:
            if self.ssd[q]['parent_id'] == startPoint:
                currentLevel.append(q)

        # check for empty directories and recurse
        emptyDirs = []
        for q in currentLevel:
            if self.ssd[q]['size'] == 0:
                emptyDirs.append(q)
        
        if len(emptyDirs) != 0:
            for q in emptyDirs:
                self.findSizes(q,depth+1)
        
        # count up and add
        tmpSize = 0
        for q in currentLevel:
            tmpSize += self.ssd[q]['size']
        self.ssd[startPoint]['size'] = tmpSize


    def dayOne(self):

        dirList = []
        for q in self.ssd:
            if self.ssd[q]['type'] == 'dir' and self.ssd[q]['size'] <= 100000:
                dirList.append(q)
        answer = 0
        for q in dirList:
            answer += self.ssd[q]['size']
        print(answer)


    def dayTwo(self):
        totalDisk = 70000000
        reqDisk = 30000000
        rootSize = self.ssd['/']['size']
        freeDisk = totalDisk - rootSize        
        target = reqDisk - freeDisk
        dirList = []

        for q in self.ssd:
            if self.ssd[q]['type'] == "dir":
                size = self.ssd[q]['size']
                if size >= target:
                    dirList.append((q, size))

        smol = dirList[0]
        for q in dirList:
            if q[1] < smol[1]:
                smol = q
        print(smol[1])

def main():

    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong with input file")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    comptroller = thisIsAUnixSystemIKnowThis(rd)

if __name__ == '__main__':
    main()