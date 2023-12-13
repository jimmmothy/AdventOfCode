import sys


class glider:
    def __init__(self, input: str):

        self.history_all = [[int(q) for q in w.split(" ")] for w in input.split('\n')]
        self.sum_of_added_right = 0
        self.sum_of_added_left = 0

        for q in self.history_all:
            self.extrapolate(q, True)
        print(self.sum_of_added_right)

        for q in self.history_all:
            self.extrapolate(q, False)
        print(self.sum_of_added_left)
        


    def extrapolate(self, input: list, right: bool):

        list_buff = []
        current_list = input.copy()
        list_buff.append(current_list)

        while self.onlyzeros(current_list) != True:
            current_list = self.difference(current_list)
            list_buff.append(current_list)

        last_added = 0
        for list_elements in reversed(list_buff):

            if right == True:
                sp_to_last_in_list = len(list_elements)-1
                last_added += list_elements[sp_to_last_in_list]
                list_elements.append(last_added)

            else:
                list_elements.reverse()               
                sp_to_last_in_list = len(list_elements)-1
                last_added = list_elements[sp_to_last_in_list] - last_added
                list_elements.append(last_added)

        if right == True:
            self.sum_of_added_right += last_added
        else:
            self.sum_of_added_left += last_added



    def onlyzeros(self, input: list) -> bool:
        onlyzeros = True
        for q in input:
            if q != 0:
                onlyzeros = False
        return onlyzeros
    


    def difference(self, input: list) -> list:
        diffs = []
        for q in range(0, len(input)-1):
            diffs.append(input[q+1]-input[q])
        return diffs


def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = glider(rd)

if __name__ == '__main__':
    main()