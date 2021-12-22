#!/usr/bin/python3

import sys

class paper:

	def __init__(self, width, height: int):

		self.width = width
		self.height = height
		self.grid = [[0 for i in range(0, self.width+1)] for j in range(0, self.height+1)]
	
	def addpoint(self, x, y: int) -> None:

		self.grid[y][x] = 1
	
	def countDots(self) -> int:

		counter = 0
		for y in range(0, self.height+1):
			for x in range(0, self.width+1):
				if self.grid[y][x] == 1:
					counter += 1
		return counter


	def printGrid(self) -> None:

		for y in range(0, self.height+1):
			tmp = ""
			for x in range(0, self.width+1):
				if self.grid[y][x] == 1:
					tmp += "#"
				else:
					tmp += " "
			print(tmp)

	def fold(self, xy, d):

		if xy == "x":
			for y in range(0, self.height+1):
				for x in range(0, d):
					offset = (abs(x - d) * 2) + x
					if self.grid[y][x] == 1 or self.grid[y][offset] == 1:
						self.grid[y][x] = 1
			self.width = d
		elif xy == "y":
			for x in range(0, self.width+1):
				for y in range(0, d):
					offset = (abs(y - d) * 2) + y
					if self.grid[y][x] == 1 or self.grid[offset][x] == 1:
						self.grid[y][x] = 1
			self.height = d

		
def main():
	
	input = open(str(sys.argv[1]), "r").read()
	points = input.split("\n\n")[0].rstrip()
	points = [x for x in points.split("\n")]
	folds = input.split("\n\n")[1].rstrip()

	width, height = 0, 0
	for z in points:
		w = int(z.split(",")[0])
		h = int(z.split(",")[1])
		if w > width:
			width = w
		if h > height:
			height = h
	width *= 2
	height *= 2
	
	foldyboi = paper(width, height)
	for q in points:
		x = int(q.split(",")[0])
		y = int(q.split(",")[1])
		foldyboi.addpoint(x, y)
	
	count = 0
	for q in folds.split("\n"):
		count += 1
		axis = q.split("=")[0][-1:]
		ammount = int(q.split("=")[1])
		foldyboi.fold(axis, ammount)
		
		if count == 1:
			print(f"{foldyboi.countDots()}\n")
	
	foldyboi.printGrid()

if __name__ == "__main__":
	main()
