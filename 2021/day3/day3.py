#/usr/bin/python3

import sys

def main():

    input = open(str(sys.argv[1]), "r")
    report = []
    for x in input:
        report.append(str(x)[:-1])


    # Part one
    gamma = ""
    epsilon = ""
    
    for q in range(0, len(report[0])-1):
        bzero = 0
        bone = 0
        for p in report:
            c_byte = int(p[q])
            if c_byte == 0:
                bzero += 1
            elif c_byte == 1:
                bone += 1
        
        if bzero > bone:
            gamma += "0"
            epsilon += "1"
        elif bone > bzero:
            gamma += "1"
            epsilon += "0"    
    power = int(gamma, 2) * int(epsilon, 2)
    print(power)

    # Part two
    tmp = report
    oxygen = 0
    for q in range(0, len(report[0])):
        tmp = oxygen_filter(tmp, q, 1)
        if len(tmp) == 1:
            oxygen = tmp[0]

    tmp = report
    c02 = 0
    for q in range(0, len(report[0])):
        tmp = oxygen_filter(tmp, q, 0)
        if len(tmp) == 1:
            c02 = tmp[0]
    
    life_support = int(oxygen, 2) * int(c02, 2)
    print(life_support)


def oxygen_filter(lval, position, bit):

    tmp = []
    bzero = 0
    bone = 0
    for p in lval:
        c_byte = int(p[position])
        if c_byte == 0:
            bzero += 1
        elif c_byte == 1:
            bone += 1

    if bit == 1:
        for p in lval:
            if bzero > bone:
                if p[position] == "0":
                    tmp.append(p)
            elif bone > bzero or bzero == bone:
                if p[position] == "1":
                    tmp.append(p)
    elif bit == 0:
        for p in lval:
            if bzero < bone or bzero == bone:
                if p[position] == "0":
                    tmp.append(p)
            elif bone < bzero:
                if p[position] == "1":
                    tmp.append(p)
            
    return tmp


if __name__ == '__main__':
    main()