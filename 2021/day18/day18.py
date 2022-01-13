#!/usr/bin/python3

import sys
import math


class potatofish:
	def __init__(self):
		self.input = ""
		self.data = self.input

	def add(self, input: str) -> None:
		if self.data == "":
			self.data = input
		else:
			self.data = "[" + self.data + "," + input + "]"

	
	def next_left(self, start: int) -> int:

		for x in reversed(range(1, start)):
			
			cp = self.new_left[x]
			cpe = self.new_left[x - 1]

			if cp.isnumeric() == True:
				if cpe.isnumeric() == False:
					return int(cp), x, False
				elif cpe.isnumeric() == True:
					return int(cpe + cp), x - 1, True
		return None, None, False
	

	def next_right(self, end: int) -> int:

		for x in range(end, len(self.new_right)-1):
			cp = self.new_right[x]
			cpe = self.new_right[x + 1]

			if cp.isnumeric() == True:
				if cpe.isnumeric() == False:
					return int(cp), x, False
				elif cpe.isnumeric() == True:
					return int(cp + cpe), x, True
		return None, None, False
	

	# replace an existing entry via pointer
	def replace_entry(self, before, after: int, value: str, target: str) -> None:

		if target == "left":
			if before == 0:
				new_data = "[" + value + self.new_left[after:]
			else:
				new_data = self.new_left[:before+1] + value + self.new_left[after:]
			self.new_left = new_data

		elif target == "right":
			new_data = self.new_right[:before] + value + self.new_right[after:]
			self.new_right = new_data

	
	def explode(self, start, end: int) -> None:
		data = self.data[start:end]

		left = int((data.split(",")[0])[1:])
		right = int((data.split(",")[1])[:-1])

		self.new_left = self.data[:start]
		self.new_right = self.data[end:]

		next_left, lp, lpe = self.next_left(start)
		next_right, rp, rpe = self.next_right(0)


		if next_left == None:
			left = 0
		else:
			left = left + next_left
			if lpe == True:
				self.replace_entry(lp-1, lp+2, str(left), "left")
			else:
				self.replace_entry(lp-1, lp+1, str(left), "left")

		if next_right == None:
			right = 0
		else:
			right = right + next_right
			if rpe == True:
				self.replace_entry(rp, rp+2, str(right), "right")
			else:
				self.replace_entry(rp, rp+1, str(right), "right")


		new_data = self.new_left + "0" + self.new_right
		self.data = new_data
	
	
	def find_pairs(self) -> str:

		pairs = []
		for x in range(0, len(self.data)-2):
			q = self.data[x]
			w = self.data[x + 1]
			e = self.data[x + 2]
			lpos, rpos = 0, 0

			if q.isnumeric() == True and e.isnumeric() == True and w == ",":

				if (self.data[x-1]).isnumeric():
					q = self.data[x-2] + self.data[x-1] + q
					lpos = x-2
				else:
					q = self.data[x-1] + q
					lpos = x-1

				if (self.data[x+3]).isnumeric():
					e = e + self.data[x+3] + self.data[x+4]
					rpos = x+5
				else:
					e = e + self.data[x+3]
					rpos = x+4

				new_str = q + w + e
				pos = tuple((lpos, rpos))
				pairs.append(tuple((new_str, pos)))
		return pairs


	def count_depth(self, depth) -> int:

		lc, rc = 0, 0
		for x in self.data[:depth+1]:
			if x == "[":
				lc += 1
			elif x == "]":
				rc += 1
		return int(abs(lc - rc))
	
	def do_explosions(self) -> bool:

		# sort out exploded
		exploded_finished = False
		explosions = False
		while exploded_finished == False:

			pairs = self.find_pairs()
			for q in pairs:
				
				val = q[0]
				start = q[1][0]
				end = q[1][1]
				depth = self.count_depth(start)
				if depth > 4:
					self.explode(start, end)
					explosions = True
					break
			
			exploded_finished = True
		return explosions
	

	def split(self, start, end: int) -> None:

		data = int(self.data[start:end])
		left = math.floor(data / 2)
		right = math.ceil(data / 2)
		self.data = self.data[:start] + "[" + str(left) + "," + str(right) + "]" + self.data[end:]
	

	def find_splitable_numbers(self) -> None:

		numbers = []
		for x in range(0, len(self.data)-1):
			q = self.data[x]
			w = self.data[x + 1]

			if q.isnumeric() == True and w.isnumeric() == True:
				val = int(q + w)
				pos = tuple((x, x + 2))
				numbers.append(tuple((val, pos)))
		return numbers
	
	def do_split(self) -> bool:

		numbers = self.find_splitable_numbers()
		if len(numbers) > 0:
			
			number = int(numbers[0][0])
			lp = numbers[0][1][0]
			rp = numbers[0][1][1]
			self.split(lp, rp)

			return True
		return False

	def needful(self) -> None:

		# look over every pair while running, left to right
		# take action on those that need it

		answer_found = False
		while answer_found == False:

			if self.do_explosions() == False and self.do_split() == False:
				answer_found = True

class pairo:
	def __init__(self, input):
		self.data = input
	
		self.mid = self.find_mid()
		self.left, self.right = self.data[1:self.mid], self.data[self.mid+1:-1]

		if self.left.isnumeric() == True:
			self.final_left = int(self.left)
		else:
			self.final_left = pairo(self.left).solution

		if self.right.isnumeric() == True:
			self.final_right = int(self.right)
		else:
			self.final_right = pairo(self.right).solution
		
		self.solution = (3 * self.final_left) + (2 * self.final_right) 

	def find_mid(self):
		lc, rc = 0, 0
		point = 0

		for q in self.data:
			if q == "[":
				lc += 1
			elif q == "]":
				rc += 1
			elif q == "," and lc - rc == 1:
				return point
		
			point += 1


def main():
	
	input = open(str(sys.argv[1]), "r").read()
	data = [x for x in input.rstrip().split("\n")]

	# part one
	potato = potatofish()
	for q in data:
		potato.add(q)
		potato.needful()
	das_list = pairo(potato.data)
	print(das_list.solution)


	# part two
	largest = 0
	data_len = len(data)
	for x in range(0, data_len-1):
		for y in range(1, data_len):

			xy = "[" + data[x] + "," + data[y] + "]"
			potato = potatofish()
			potato.add(xy)
			potato.needful()
			xyv = pairo(potato.data).solution

			if xyv > largest:
				largest = xyv

			yx = "[" + data[y] + "," + data[x] + "]"
			potato = potatofish()
			potato.add(yx)
			potato.needful()
			yxv = pairo(potato.data).solution

			if yxv > largest:
				largest = yxv
	print(largest)


if __name__ == "__main__":
	main()
