#!/usr/bin/python3

import sys

class target_area:
	def __init__(self, input):
		self.input = input
		
		self.x1 = int((input.split(" ")[2].split("..")[0])[2:])
		self.x2 = int((input.split(" ")[2].split("..")[1])[:-1])
		
		self.y1 = int((input.split(" ")[3].split("..")[0])[2:])
		self.y2 = int(input.split(" ")[3].split("..")[1])
	
	def check_target_area(self, x, y: int) -> bool:
		if x >= self.x1 and x <= self.x2:
			if y >= self.y1 and y <= self.y2:
				return True
		return False
	
	def check_overshoot(self, x, y: int) -> bool:
		xo, yo = False, False
		if x > self.x2:
			xo = True
		if y < self.y2:
			yo = True
		return xo, yo

class probe:
	def __init__(self, xvelocity, yvelocity: int, target_area):
		self.x = 0
		self.y = 0
		self.xvelocity = xvelocity
		self.yvelocity = yvelocity
		self.target_reached = False
		self.overshot_target = False
		self.undershot_target = False
		self.target_area = target_area
		self.highest_y = 0

		# run till we have an end
		while self.target_reached == False and self.overshot_target == False and self.undershot_target == False:
			self.process_turn()
	
	def turn_events(self):

		self.x += self.xvelocity
		self.y += self.yvelocity
		
		if self.xvelocity > 0:
			self.xvelocity -= 1
		elif self.xvelocity < 0:
			self.xvelocity += 1

		self.yvelocity -= 1
	
	def process_turn(self):
		self.turn_events()

		if self.y > self.highest_y:
			self.highest_y = self.y

		xo, yo = self.target_area.check_overshoot(self.x, self.y)

		if self.target_area.check_target_area(self.x, self.y) == True:
			self.target_reached = True
		elif xo and yo == True:
			self.overshot_target = True
		elif yo == True and self.xvelocity == 0:
			self.undershot_target = True

def main():
	input = open(str(sys.argv[1]), "r").read()
	input = input.rstrip()

	hot_lz = target_area(input)
	highest_y = 0
	total_reaching_target = 0

	for x in range(1, hot_lz.x2+1):

		count = hot_lz.y1
		while count < abs(hot_lz.y1):

			tmp = probe(x, count, hot_lz)	
			count += 1				

			if tmp.target_reached == True and tmp.highest_y > highest_y:
				highest_y = tmp.highest_y
			if tmp.target_reached == True:
				total_reaching_target += 1

	# part one
	print(highest_y)

	# part two
	print(total_reaching_target)

if __name__ == "__main__":
	main()
