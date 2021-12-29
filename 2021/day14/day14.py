#!/usr/bin/python3

import sys

class polymer:

	def __init__(self, input):
		self.template = input.split("\n\n")[0]
		self.moves = [x for x in ((input.rstrip()).split("\n\n")[1]).split("\n")]
		self.length = len(self.template)
		self.letters = {}

		self.combos = {}
		for q in self.moves:
			initial = q.split(" -> ")[0]
			if initial not in self.combos:
				self.combos[initial] = 0
			else:
				self.combos[initial] = 0
		self.buildcombos(self.template)

		self.lettercount = {}
		for q in self.template:
			if q not in self.lettercount:
				self.lettercount[q] = 1
			else:
				self.lettercount[q] += 1

	def buildcombos(self, input) -> None:

		length = len(input)
		for q in range(0, length-1):
			buff = input[q] + input[q + 1]
			if buff not in self.combos:
				self.combos[buff] = 1
			else:
				self.combos[buff] += 1

	def insertcombo(self, initial, insert, combos, ammount) -> None:

		self.length += ammount

		offshoot1 = initial[0] + insert
		offshoot2 = insert + initial[1]

		if offshoot1 not in combos:
			combos[offshoot1] = ammount
		else:
			combos[offshoot1] += ammount

		if offshoot2 not in combos:
			combos[offshoot2] = ammount
		else:
			combos[offshoot2] += ammount


		if insert not in self.lettercount:
			self.lettercount[insert] = ammount
		else:
			self.lettercount[insert] += ammount
				
		return combos
		
	
	def nextmove(self) -> bool:
		
		tmpcombos = self.combos.copy()
		for q in self.moves:
			initial = q.split(" -> ")[0]
			insert = q.split(" -> ")[1]

			if self.combos[initial] >= 1:
				ammount = self.combos[initial]

				tmpcombos[initial] -= ammount
				tmpcombos = self.insertcombo(initial, insert, tmpcombos, ammount)
		
		self.combos = tmpcombos.copy()
		return True
	
	def countallletters(self) -> None:

		mostcommon = 0
		leastcommon = 0
		first = True

		for q in self.lettercount:

			value = self.lettercount[q]
			if first == True:
				first = False
				leastcommon = value
				mostcommon = value

			else:
				if value < leastcommon:
					leastcommon = value
				elif value > mostcommon:
					mostcommon = value

		print(f"{mostcommon - leastcommon}")


def main():
	
	
	input = open(str(sys.argv[1]), "r").read()
	plastic = polymer(input)

	step = 0
	limit = 10
	while (step < limit):
		plastic.nextmove()
		step += 1
	plastic.countallletters()

	limit = 40
	while (step < limit):
		plastic.nextmove()
		step += 1
	
	plastic.countallletters()


if __name__ == "__main__":
	main()