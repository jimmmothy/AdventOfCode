#!/usr/bin/python3

import sys

class polymer:

	def __init__(self, input):
		self.template = input.split("\n\n")[0]
		self.moves = [x for x in ((input.rstrip()).split("\n\n")[1]).split("\n")]
		self.length = len(self.template)
		self.letters = []
	
	def checkinsert(self, input) -> str:

		for q in self.moves:
			template = q.split(" -> ")[0]
			insertion = q.split(" -> ")[1]

			if template == input:
				return insertion
		return ""
	
	def nextmove(self) -> bool:

		inserted = False
		buff = self.template
		temp = ""

		for q in range(0, len(self.template)-1):
			target = self.template[+q:q+2]
			insert = self.checkinsert(target)

			if insert != "":
				if q != 0:
					fullinsert = insert + target[1]
				else:
					fullinsert = target[0] + insert + target[1]
				temp += fullinsert
				inserted = True
		
		self.template = temp
		return inserted

	def letterfound(self, input) -> bool:

		for q in self.letters:
			if q != [] and q[0] == input:
				return True
		return False
	
	def addtoletter(self, letter, ammount) -> None:

		for q in range(0, len(self.letters)):
			if self.letters[q] != [] and self.letters[q][0] == letter:
				extra = self.letters[q][1]
				self.letters[q] = tuple((letter, extra+ammount))

	def countletters(self) -> int:

		self.letters = []
		self.length = len(self.template)
		for q in self.template:
			if self.letterfound(q) == True:
				self.addtoletter(q, 1)
			else:
				self.letters.append(tuple((q, 1)))
				a = tuple((q, 1))

		
		if self.letters != []:
			totalcount = 0
			highest, lowest = 0, self.letters[0][1]
			for q in self.letters:
				totalcount += 1
				if q[1] < lowest:
					lowest = q[1]
				elif q[1] > highest:
					highest = q[1]
			return (highest - lowest)
		
		return 0



def main():
	
	
	input = open(str(sys.argv[1]), "r").read()
	plastic = polymer(input)

	print(f"{plastic.template}\n{plastic.moves}")

	step = 0
	limit = 10
	while (plastic.nextmove() == True and step < limit):
		step += 1
		count = plastic.countletters()
		#print(f"After step {step}: {plastic.template}")
	print(count)

	limit = 40
	while (plastic.nextmove() == True and step < limit):
		step += 1
		
		#print(f"After step {step}: {plastic.template}")
		print(f"{step} of {limit}")
	count = plastic.countletters()

if __name__ == "__main__":
	main()