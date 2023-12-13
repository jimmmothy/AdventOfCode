import sys
import numpy as np

class automoton:
    def __init__(self, name: str):
        self.name = name
        self.on_z = False
        self.step_count = 0
        self.current_spot = name
        self.first_z = 0

    def doMove(self, move_to: str):

        self.current_spot = move_to        
        self.step_count += 1

        # on a Z?
        if self.current_spot[2:] == "Z":
            self.on_z = True
            
            if self.first_z == 0:
                self.first_z = self.step_count
        else:
            self.on_z = False


class controller:
    def __init__(self, input: str):

        self.instructions = list(input.split('\n\n')[0])
        self.map = input.split('\n\n')[1].split('\n')
        self.elements = {}
        self.createElements(self.map)
        self.start_points = []
        
        for q in self.elements:
            if self.elements[q][2][2:] == "A":
                self.start_points.append(automoton(self.elements[q][2]))

        move_sp = 0
        first_z_dict = {}
        
        end_found = False
        while end_found == False:

            if move_sp == len(self.instructions):
                move_sp = 0

            for q in self.start_points:
            
                if q.first_z > 0 and q.name not in first_z_dict:
                    first_z_dict[q.name]=q.first_z
                
                else:
                    move_instruction = self.instructions[move_sp]
                    if move_instruction == "L":
                        move_to = self.elements[q.current_spot][0]
                    elif move_instruction == "R":
                        move_to = self.elements[q.current_spot][1]

                    q.doMove(move_to)

            move_sp += 1
            
            if len(first_z_dict) == len(self.start_points):
                end_found = True
                
        lcm = np.lcm.reduce([first_z_dict[q] for q in first_z_dict])
        print(lcm)
        
    
    def createElements(self, input: list):

        for q in input:
            e_name = q.split(" = ")[0]
            e_left = q.split(" = (")[1].split(',')[0]
            e_right = q.split(", ")[1][:-1]
            self.elements[e_name] = ((e_left, e_right, e_name))
                    

def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = controller(rd)

if __name__ == '__main__':
    main()