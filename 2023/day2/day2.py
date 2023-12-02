import sys

class game:
    def __init__(self, id: int):
        self.id = id
        #self.set = []
        self.max_rgb = [0,0,0]


class gamer:
    def __init__(self, input: str):
        self.input = input
        self.games = []

        for x in self.input.split('\n'):
            self.parseGame(x)
        
        ## day 1
        games_passing_sum = 0
        limits = [12,13,14]

        for q in self.games:
            if q.max_rgb[0] <= limits[0] and q.max_rgb[1] <= limits[1] and q.max_rgb[2] <= limits[2]:
                games_passing_sum += q.id
        print(f"{games_passing_sum}")


        ## day 2
        value = 0
        for q in self.games:
            value += q.max_rgb[0] * q.max_rgb[1] * q.max_rgb[2]
        print(f"{value}")

    def parseGame(self, input: str):

        id = int(input.split(": ")[0].split(" ")[1])
        remainder = input.split(": ")[1]
        set_input = remainder.split("; ")
        game_buff = game(id)

        for q in set_input:
            red, green, blue = 0, 0, 0
            w = q.split(", ")
            for e in w:
                num = int(e.split(" ")[0])
                colour = e.split(" ")[1]
                if colour == "red":
                    red = num
                elif colour == "green":
                    green = num
                elif colour == "blue":
                    blue = num

            if game_buff.max_rgb[0] < red:
                game_buff.max_rgb[0] = red
            if game_buff.max_rgb[1] < green:
                game_buff.max_rgb[1] = green
            if game_buff.max_rgb[2] < blue:
                game_buff.max_rgb[2] = blue
            
        self.games.append(game_buff)

        


def main():

    if len(sys.argv) != 2:
        print("Something wrong!")

    rd = open(str(sys.argv[1]), "r").read().rstrip()
    comptroller = gamer(rd)

if __name__ == '__main__':
    main()