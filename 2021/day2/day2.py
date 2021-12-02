#/usr/bin/python3

import sys

def main():

    input = open(str(sys.argv[1]), "r")
    moves = []
    for x in input:
        moves.append(str(x))


    # Part one
    depth = 0
    hpos = 0

    for x in moves:
        type = x.split(" ")[0]
        distance = int(x.split(" ")[1])

        if type == "forward":
            hpos += distance
        elif type == "down":
            depth += distance
        elif type == "up":
            depth -= distance

    print(depth * hpos)

    # Part two
    depth = 0
    hpos = 0
    aim = 0

    for x in moves:
        type = x.split(" ")[0]
        val = int(x.split(" ")[1])

        if type == "forward":
            hpos += val
            depth += aim * val
        elif type == "down":
            aim += val
        elif type == "up":
            aim -= val
            
    print(depth * hpos)

if __name__ == '__main__':
    main()