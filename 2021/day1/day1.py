#/usr/bin/python3

import sys

def main():

    input = open(str(sys.argv[1]), "r")
    depths = []
    for x in input:
        depths.append(int(str(x)[:-1]))

# Part one
    inc = 0
    distance = 0
    previous = 0
    for q in depths:
        if distance != 0:
            if q > previous:
                inc += 1
            
        previous = int(q)
        distance += 1

    print(inc)


# Part two
    inc = 0
    previous = 0
    current = 0
    for x in range(0, len(depths)-2):

        if x == 0:
            continue

        current = depths[x] + depths[x + 1] + depths[x + 2]
        if current > previous:
            inc += 1
    
        previous = current
    print(inc)

if __name__ == '__main__':
    main()