import sys

class controller:
    def __init__(self, input: str):

        self.instructions = list(input.split('\n\n')[0])
        self.map = input.split('\n\n')[1].split('\n')
        self.elements = {}
        self.createElements(self.map)

        self.step_count = 0
        self.current_spot = "AAA"
        self.sp = 0

        while self.current_spot != "ZZZ":

            if self.sp == len(self.instructions):
                self.sp = 0

            move = self.instructions[self.sp]
            if move == "L":
                self.current_spot = self.elements[self.current_spot][0]
            elif move == "R":
                self.current_spot = self.elements[self.current_spot][1]
            
            self.sp += 1
            self.step_count += 1

        print(f"steps:{self.step_count}")
    
    def createElements(self, input: list):

        for q in input:
            e_name = q.split(" = ")[0]
            e_left = q.split(" = (")[1].split(',')[0]
            e_right = q.split(", ")[1][:-1]
            self.elements[e_name] = ((e_left, e_right))
                    

def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = controller(rd)

if __name__ == '__main__':
    main()