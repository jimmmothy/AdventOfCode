#!/usr/bin/python3

import sys

class monkey:
    def __init__(self, id: int, items: list, operator: str, operand: str, test: int, trueMonkey: int, falseMonkey: int):
        self.id = id
        self.items = items
        self.ic = len(self.items)
        self.operator = operator
        self.operand = operand
        self.test = test
        self.trueMonkey = trueMonkey
        self.falseMonkey = falseMonkey
        self.inspectioncount = 0
    

    def addItem(self, worry: int):
        self.items.append(worry)
        self.ic += 1


    def inspectItem(self, divisor: int) -> tuple:
        self.inspectioncount += 1
        worry = self.items.pop(0)
        self.ic -= 1
        op2 = 0
        
        if self.operand.isdigit() == True:
            op2 = int(self.operand)
        else:
            op2 = worry
        
        if self.operator == "*":
            worry = worry * op2
        elif self.operator == "+":
            worry = worry + op2
        
        if divisor == 3:
            worry = int(worry / divisor)
        else:
            worry = int(worry % divisor)

        if worry % self.test == 0:
            return tuple((worry, self.trueMonkey))
        else:
            return tuple((worry, self.falseMonkey))


class monkeyd:
    def __init__(self):
        self.monkeys: list[monkey] = []
    

    def findAnswer(self):
        ic = []
        for q in self.monkeys:
            ic.append(q.inspectioncount)
        ic.sort(reverse=True)
        print(ic[0] * ic[1])


    def dayOne(self, rounds: int) -> None:
        for _ in range(0, rounds):
            self.doRound(3)
    

    def dayTwo(self, rounds: int) -> None:
        for _ in range(0, rounds):
            
            div = 1
            for w in [chimp.test for chimp in self.monkeys]:
                div *= w
            self.doRound(div)


    def doRound(self, divisor: int) -> None:
        for q in range(0, len(self.monkeys)):

            cm = self.monkeys[q]
            if cm.ic == 0:
                continue

            while cm.ic != 0:
                movement = cm.inspectItem(divisor)
                self.monkeys[movement[1]].addItem(movement[0])


    def addMonkey(self, input: str) -> None:
        sinput = input.split('\n')

        id = int(sinput[0][7:-1])
        items = [int(x) for x in sinput[1][18:].split(', ')]
        operator = sinput[2][23:].split(' ')[0]
        operand = sinput[2][23:].split(' ')[1]
        test = int(sinput[3][21:])
        trueMonkey = int(sinput[4][29:])
        falseMonkey = int(sinput[5][30:])

        self.monkeys.append(monkey(id, items, operator, operand, test, trueMonkey, falseMonkey))


def main():
    inputFile = ""
    try:
        inputFile = str(sys.argv[1])
    except IndexError:
        print("Something went wrong with input file")
        return 1

    rd = open(inputFile, "r").read().rstrip()
    input = [z for z in rd.split('\n\n')]

    themonkeys = monkeyd()
    for q in input:
        themonkeys.addMonkey(q)
    themonkeys.dayOne(20)
    themonkeys.findAnswer()

    themonkeys = monkeyd()
    for q in input:
        themonkeys.addMonkey(q)
    themonkeys.dayTwo(10000)
    themonkeys.findAnswer()

if __name__ == '__main__':
    main()