import sys

class calibrator:
    def __init__(self, input: str):
        self.input = input

        value = 0
        for x in self.input.split('\n'):
            value += self.findCal(x)
        print(value)

        value = 0
        sum = 0
        for x in self.input.split('\n'):
            value = self.findCalBetter(x)
            sum += value
        print(sum)

    # Day 1
    def findCal(self, input: str) -> int:
        
        digits = []
        for x in input:
            if x.isdigit():
                digits.append(x)
        
        if len(digits) == 1:
            return int(digits[0]+digits[0])
        elif len(digits) == 2:
            return int(digits[0]+digits[1])
        elif len(digits) >2:
            return int(digits[0]+digits[len(digits)-1])
        
    

    # Day 2
    def findCalBetter(self, input: str) -> int:

        digits = []
        pc = 0
        pc_lim = len(input)
        str_buff = ""

        while pc < pc_lim:
            if input[pc].isdigit():
                str_buff = ""
                digits.append(input[pc])
                pc += 1

            else:
                str_buff = ""

                y = pc
                counter = 0
                while y+counter < pc_lim and counter < 6:
                    str_buff += input[y+counter]
                    counter += 1

                    response = ''
                    response = self.alphaNumber(str_buff)
                    if response != '0':
                        digits.append(response)
                        y = pc_lim
                pc += 1
        
        if len(digits) == 1:
            return int(digits[0]+digits[0])
        elif len(digits) == 2:
            return int(digits[0]+digits[1])
        elif len(digits) > 2:
            return int(digits[0]+digits[len(digits)-1])
        else:
            return 0
        
                    

    def alphaNumber(self, input: str) -> int:

        if input == "one":
            return '1'
        elif input == "two":
            return '2'
        elif input == "three":
            return '3'
        elif input == "four":
            return '4'
        elif input == "five":
            return '5'
        elif input == "six":
            return '6'
        elif input == "seven":
            return '7'
        elif input == "eight":
            return '8'
        elif input == "nine":
            return '9'
        else:
            return '0'


def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = calibrator(rd)

if __name__ == '__main__':
    main()