import sys


class tatts:
    def __init__(self, input: str):
        self.input = input.split('\n')

        ## day 1
        self.score = 0
        for q in self.input:
            self.score += self.parseTicket(q)
        print(self.score)


        ## day 2
        self.cardCopies = [1] * len(self.input)

        for q in self.input:
            matches, id = self.parseTicketCopies(q)

            copiesOfCurrCard = self.cardCopies[id-1]
            for e in range(0, copiesOfCurrCard):
                for w in range(0, matches):
                    self.cardCopies[id+w] += 1
                    
        scratchies = 0
        for q in self.cardCopies:
            scratchies += q
        print(scratchies)


    def parseTicketCopies(self, input: str) -> int:

        z = input.split(':')[0].split(' ')
        id = int(z[len(z)-1])

        winningNumbers = self.parseNumbers(input.split(": ")[1].split(" | ")[0])
        myNumbers = self.parseNumbers(input.split(": ")[1].split(" | ")[1])

        matches = 0
        for q in myNumbers:
            if q in winningNumbers:
                matches += 1
        return matches,id
    


    def parseNumbers(self, input: list) -> list:
        numbers = []
        for q in input.split(" "):
            if q.isdigit():
                numbers.append(int(q))
        return numbers

    
    def parseTicket(self, input: str) -> int:

        winningNumbers = self.parseNumbers(input.split(": ")[1].split(" | ")[0])
        myNumbers = self.parseNumbers(input.split(": ")[1].split(" | ")[1])

        score = 0
        for q in myNumbers:
            if q in winningNumbers:
                if score == 0:
                    score = 1
                else:
                    score *= 2
        return score


def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = tatts(rd)

if __name__ == '__main__':
    main()