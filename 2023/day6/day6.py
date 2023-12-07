import sys


class motorboat:
    def __init__(self, input: str):

        time_raw = input.split('\n')[0].split(":")[1].split(" ")
        self.times = []
        kern_time_tmp = ""
        for q in time_raw:
            if q.isdigit():
                kern_time_tmp += q
                self.times.append(int(q))
        self.kern_time = int(kern_time_tmp)

        distance_raw = input.split('\n')[1].split(":")[1].split(" ")
        self.distances = []
        kern_distance_tmp = ""
        for q in distance_raw:
            if q.isdigit():
                kern_distance_tmp += q
                self.distances.append(int(q))
        self.kern_distance = int(kern_distance_tmp)
        self.total_races = len(self.times)

        self.dayOne()
        self.dayTwo()


    def dayTwo(self):
        ways_to_win = 0
        answer = 1
        for charge in range(0, self.kern_time):
            distance_travelled = self.doRace(self.kern_time, charge)
            if distance_travelled > self.kern_distance:
                ways_to_win += 1
        
        if ways_to_win > 0:
            answer = answer * ways_to_win
        print(ways_to_win)



    def dayOne(self):

        answer = 1
        for c_time,c_distance in zip(self.times,self.distances):
            ways_to_win = 0

            for charge in range(0, c_time):
                distance_travelled = self.doRace(c_time, charge)
                if distance_travelled > c_distance:
                    ways_to_win += 1
            
            if ways_to_win > 0:
                answer = answer * ways_to_win
        print(answer)

        

    def doRace(self, time: int, charge: int) -> int:
        return(charge*(time-charge))


def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = motorboat(rd)

if __name__ == '__main__':
    main()