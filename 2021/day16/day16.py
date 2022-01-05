#!/usr/bin/python3

import sys

class packet:

	def __init__(self, input):
		self.number_of_subpackets = 0
		self.full_value_str = ""
		self.length_type_id = 0
		self.input = input
		self.decoded_value = 0
		self.packets = []
		self.packet_length = 6
		self.packet_version, self.packet_type_id = self.basic_analysis(input)

		# literal packet
		if self.packet_type_id == 4:

			buff = 6
			end_found = False
			tmp_val = ""

			while end_found == False:

				z = self.input[buff]
				tmp_val += self.input[buff+1:buff+5]
				
				if z == "0":
					end_found = True
				else:
					buff += 5

			self.packet_length = buff + 5
			self.decoded_value = int(tmp_val, 2)

		# operator packet
		else:
			
			# grab length_type_id
			self.length_type_id = self.get_length_type_id()

			# case one
			if self.length_type_id == 0:

				self.packet_length += 16
				self.length_of_subpackets = self.get_length_of_subpackets()
				self.packetdata = self.get_subpacket_data(22)
				buff = 0

				while self.length_of_subpackets > buff:

					new_packet = packet(self.packetdata)
					self.packets.append(new_packet)
					buff += new_packet.packet_length
					self.packetdata = self.get_subpacket_data(22+buff)
				
				self.packet_length += buff

			# case two
			elif self.length_type_id == 1:
				self.packet_length += 12
				self.number_of_subpackets = self.get_number_of_subpackets()
				self.packetdata = self.get_subpacket_data(18)

				buff = 0
				for q in range(0, self.number_of_subpackets):

					new_packet = packet(self.packetdata)
					self.packets.append(new_packet)
					buff += new_packet.packet_length
					self.packetdata = self.get_subpacket_data(18+buff)
				
				self.packet_length += buff

			if self.packet_type_id == 0:
				for q in self.packets:
					self.decoded_value += q.decoded_value
			
			elif self.packet_type_id == 1:
				if len(self.packets) == 1:
					self.decoded_value = self.packets[0].decoded_value
				else:
					self.decoded_value = self.packets[0].decoded_value
					for q in range(1, len(self.packets)):
						self.decoded_value *= self.packets[q].decoded_value
			
			elif self.packet_type_id == 2:
				min = self.packets[0].decoded_value
				for q in self.packets:
					if q.decoded_value < min:
						min = q.decoded_value
				self.decoded_value = min
			
			elif self.packet_type_id == 3:
				max = self.packets[0].decoded_value
				for q in self.packets:
					if q.decoded_value > max:
						max = q.decoded_value
				self.decoded_value = max
			
			elif self.packet_type_id == 5:
				if self.packets[0].decoded_value > self.packets[1].decoded_value:
					self.decoded_value = 1
				else:
					self.decoded_value = 0
			
			elif self.packet_type_id == 6:
				if self.packets[0].decoded_value < self.packets[1].decoded_value:
					self.decoded_value = 1
				else:
					self.decoded_value = 0

			elif self.packet_type_id == 7:
				if self.packets[0].decoded_value == self.packets[1].decoded_value:
					self.decoded_value = 1
				else:
					self.decoded_value = 0
			
	def fetch_sum_of_version(self) -> int:
		tmp = self.packet_version
		if self.packets != []:
			for q in self.packets:
				tmp += q.fetch_sum_of_version()

		return tmp
	
	def basic_analysis(self, input) -> int:
		packet_version = int(self.input[:3], 2)
		packet_type_id = int(self.input[3:6], 2)

		return packet_version, packet_type_id

	def get_literal_packets(self) -> list:
		binput = self.decoinputded
		packets = []
		packets.append(binput[7:11])
		packets.append(binput[12:16])
		packets.append(binput[17:21])
		
		return packets
	
	def get_length_type_id(self) -> int:
		length_type_id = int(self.input[6:7])
		return length_type_id
	
	def get_subpacket_data(self, buff) -> str:
		packetdata = self.input[buff:]
		return packetdata

	
	def get_length_of_subpackets(self) -> int:
		length_of_subpackets = int(self.input[7:22], 2)
		return length_of_subpackets
	
	def get_number_of_subpackets(self) -> int:
		number_of_subpackets = int(self.input[7:18], 2)
		return number_of_subpackets


def hex_to_bstr(input) -> str:
	bstr = ""
	for q in input:
		if q == "0":
			bstr += "0000"
		elif q == "1":
			bstr += "0001"
		elif q == "2":
			bstr += "0010"
		elif q == "3":
			bstr += "0011"
		elif q == "4":
			bstr += "0100"
		elif q == "5":
			bstr += "0101"
		elif q == "6":
			bstr += "0110"
		elif q == "7":
			bstr += "0111"
		elif q == "8":
			bstr += "1000"
		elif q == "9":
			bstr += "1001"
		elif q == "A":
			bstr += "1010"
		elif q == "B":
			bstr += "1011"
		elif q == "C":
			bstr += "1100"
		elif q == "D":
			bstr += "1101"
		elif q == "E":
			bstr += "1110"
		elif q == "F":
			bstr += "1111"
	return bstr


def main():
	
	data = hex_to_bstr(open(str(sys.argv[1]), "r").read())
	testbed = packet(data)

	# part one
	print(f"{testbed.fetch_sum_of_version()}")

	# part two
	print(f"{testbed.decoded_value}")

if __name__ == "__main__":
	main()