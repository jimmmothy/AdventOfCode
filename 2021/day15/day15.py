#!/usr/bin/python3

'''blatant theft of Dijkstra implementation, call the feds'''

import sys


class graphed:

	def __init__(self, input):
		self.data = input
		self.width = len(input[0])
		self.height = len(input)

		self.total = len(self.data)
		self.final_node = str(self.width - 1) + "," + str(self.height - 1)
		self.nodes = []
		self.graph = {}

	def make_graph(self, total: int) -> dict:
		nodes = [x for x in range(0, total)]
		init_graph = {}
		for node in nodes:
			init_graph[node] = {}

		return init_graph

	def build_nodes(self):
		for y in range(0, self.height):
			for x in range(0, self.width):
				current = self.xy_to_str(x, y)
				if current not in self.nodes:
					self.nodes.append(current)


	def get_nodes(self) -> list:

		ls = []
		for x in self.nodes:
			ls.append(x)
		return ls

	def xy_to_str(self, x, y: int) -> int:
		tmp = str(x) + "," + str(y)
		return tmp

	def str_to_xy(self, node: str) -> int:
		x = int(node.split(",")[0])
		y = int(node.split(",")[1])
		return x, y

	def get_outgoing_edges(self, node):
		connections = []
		nx, ny = self.str_to_xy(node)
		if ny != 0:
			connections.append(self.xy_to_str(nx, ny-1))
		if ny < self.height-1:
			connections.append(self.xy_to_str(nx, ny+1))
		if nx != 0:
			connections.append(self.xy_to_str(nx-1, ny))
		if nx < self.width-1:
			connections.append(self.xy_to_str(nx+1, ny))

		return connections
	
	def value(self, node1, node2):
		a,s = self.str_to_xy(node2)
		t = self.data[s][a]
		return t
	def dijkstra_algo(self, graph, start_node):
		unvisited_nodes = list(self.get_nodes())
		shortest_path = {}
		previous_nodes = {}

		max_value = sys.maxsize
		for node in unvisited_nodes:
			shortest_path[node] = max_value
		shortest_path[start_node] = 0
		
		while unvisited_nodes:
			
			current_min_node = None
			for node in unvisited_nodes:
				if current_min_node == None:
					current_min_node = node
				elif shortest_path[node] < shortest_path[current_min_node]:
					current_min_node = node

			neighbors = self.get_outgoing_edges(current_min_node)
			
			for neighbor in neighbors:
				a = self.value(current_min_node, neighbor)
				tentative_value = shortest_path[current_min_node] + self.value(current_min_node, neighbor)
				if tentative_value < shortest_path[neighbor]:
					shortest_path[neighbor] = tentative_value
					previous_nodes[neighbor] = current_min_node

			unvisited_nodes.remove(current_min_node)

		return previous_nodes, shortest_path

def enhance(input, nth):

	basic_grid = [[int(x) for x in y] for y in input.rstrip().split("\n")]
	basic_width = len(basic_grid[0])
	basic_height = len(basic_grid)

	new_width = basic_width * nth
	new_height = basic_height * nth
	new_grid = []

	# copy first basic over down to bottom
	for y in range(0, new_height):
		tmp = []
		ymod = 0
		inc = 0
		for x in range(0, new_width):

			if y < basic_height and x < basic_width:
				tmp.append(basic_grid[y][x])
			
			else:
				if y >= basic_height:
					ymod = y - basic_height
					inc = 1

				if x >= basic_width:
					tmp.append(0)
				else:
					new_val = new_grid[ymod][x] + inc
					if new_val > 9:
						new_val %= 9
					tmp.append(new_val)
		new_grid.append(tmp)

	# Fill in rest
	for y in range(0, new_height):
		xmod = 0
		inc = 1
		for x in range(basic_width, new_width):
			
			xmod = x - (basic_width)
			new_val = new_grid[y][xmod] + inc
			if new_val > 9:
				new_val %= 9
			new_grid[y][x] = new_val
	
	return new_grid

def main():
	input = open(str(sys.argv[1]), "r").read()
	data = [[int(x) for x in y] for y in input.rstrip().split("\n")]
	das_graph = graphed(data)
	das_graph.build_nodes()
	path, distance = das_graph.dijkstra_algo(das_graph.graph, "0,0")
	print(f"{distance[das_graph.final_node]} to reach {das_graph.final_node}")

	# make the input 5x for part 2

	new_grid = enhance(input, 5)
	das_graph = graphed(new_grid)
	print("About to start building nodes")
	das_graph.build_nodes()
	print("nodes build")
	path, distance = das_graph.dijkstra_algo(das_graph.graph, "0,0")
	print(f"{distance[das_graph.final_node]} to reach {das_graph.final_node}")

if __name__ == "__main__":
	main()
