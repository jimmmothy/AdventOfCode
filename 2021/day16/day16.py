#!/usr/bin/python3

import sys

'''
packet_type_id 4: literal
packet_version
A/B/C

packet_type_id != 4 && length_type_id == 9
packet_version
length_type_id
length_of_subpackets
A/B/C

packet_type_id != 4 && length_type_id == 9
packet_version
length_type_id
number_of_subpackets
A/B/C
'''

sum_of_version = 0

class packet:

	def __init__(self, input):
		self.subpacket_data = ""
		self.number_of_subpackets = 0
		self.packets = []
		self.full_value_str = ""
		self.length_type_id = 0
		self.input = input
		self.decoded = input
		self.decoded_value = 0

		self.packet_version, self.packet_type_id = self.basic_analysis(input)
		print(f"\n\ndecoded:{self.decoded}\npacket_version:{self.packet_version}\npacket_type_id:{self.packet_type_id}")

		# Part one
		global sum_of_version
		sum_of_version += self.packet_version

		# literal packet
		if self.packet_type_id == 4:

			values = []
			buff = 6
			end_found = False

			while end_found == False:

				z = self.input[buff]
				values.append(self.input[buff+1:buff+5])
				if z == "0":
					end_found = True
				else:
					buff += 5

			remainder = self.input[buff+5:]
			print(f"{values}")

			if int(remainder, 2) != 0:
				packet(remainder)

		# non-literal packet
		else:

			# grab length_type_id
			self.length_type_id = self.get_length_type_id()
			print(f"length_type_id:{self.length_type_id}")

			# case two
			if self.length_type_id == 0:
				self.length_of_subpackets = self.get_length_of_subpackets()
				print(f"length_of_subpackets:{self.length_of_subpackets}")

				self.packetdata = self.get_subpacket_data(22)
				print(f"subpacket_data:{self.packetdata}")

				self.packets.append(packet(self.packetdata))
			
			# case three
			elif self.length_type_id == 1:
				self.number_of_subpackets = self.get_number_of_subpackets()
				print(f"number_of_subpackets:{self.number_of_subpackets}")

				self.packetdata = self.get_subpacket_data(18)
				self.packets.append(packet(self.packetdata))

	
	def basic_analysis(self, input):

		packet_version = int(self.decoded[:3], 2)
		packet_type_id = int(self.decoded[3:6], 2)

		return packet_version, packet_type_id

	def get_literal_packets(self):
		
		binput = self.decoded
		packets = []
		packets.append(binput[7:11])
		packets.append(binput[12:16])
		packets.append(binput[17:21])
		return packets
	
	def get_length_type_id(self):

		length_type_id = int(self.decoded[6:7])
		return length_type_id
	
	def get_subpacket_data(self, buff):

		packetdata = self.decoded[buff:]
		return packetdata

	
	def get_length_of_subpackets(self):

		length_of_subpackets = int(self.decoded[7:22], 2)
		return length_of_subpackets
	
	def get_number_of_subpackets(self):

		number_of_subpackets = int(self.decoded[7:18], 2)
		return number_of_subpackets
	
	def get_packets_id_one(self):

		packets = []
		#buff = 0
		#for q in range(0, self.number_of_subpackets):
		#	packets.append(self.decoded[18+buff:18+buff+11])
		#	buff += 11
		
		#packet_str = self.decoded[18:]
		#print(f"packet_str:{packet_str}")
		
		#for q in range(0, self.number_of_subpackets):
		#	packets.append(packet(coded_packet_str))

		return packets

	#def get_packets_id_zero(self):

	#	packets = []
	#	packets.append(self.packetdata)
	#	return packets

	def analyse_packet(self, input):

		binput = self.hex_to_bstr(input)

		packet_version = int(binput[:3], 2)
		packet_type_id = int(binput[3:6], 2)
		length_type_id = 0
		packets = []
		subpackets = []

		if packet_type_id == 4:
			# Not an operator
			packet_A = binput[7:11]
			packet_B = binput[12:16]
			packet_C = binput[17:21]

			packets.append(packet_A)
			packets.append(packet_B)
			packets.append(packet_C)
		
		else:
			# Operator
			length_type_id = binput[6:7]

			if length_type_id == 0:
				print("lke")
				length_of_subpackets = int(binput[7:22], 2)
				subpackets.append(binput[22:22+length_of_subpackets])

			elif length_type_id == 1:
				number_of_subpackets = int(binput[7:18], 2)

				buff = 0
				for q in range(0, number_of_subpackets):
					packets.append(binput[18+buff:18+buff+11])
					buff += 11
			
		return packet_version, packet_type_id, packets, subpackets, length_type_id


def hex_to_bstr(input):
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

def bstr_to_hex(input):
	bstr = ""
	for a in range(0, len(input)-4, 4):
			if input[a:a+4] == "0000":
				bstr += "0"
			elif input[a:a+4] == "0001":
				bstr += "1"
			elif input[a:a+4] == "0010":
				bstr += "2"
			elif input[a:a+4] == "0011":
				bstr += "3"
			elif input[a:a+4] == "0100":
				bstr += "4"
			elif input[a:a+4] == "0101":
				bstr += "5"
			elif input[a:a+4] == "0110":
				bstr += "6"
			elif input[a:a+4] == "0111":
				bstr += "7"
			elif input[a:a+4] == "1000":
				bstr += "8"
			elif input[a:a+4] == "1001":
				bstr += "9"
			elif input[a:a+4] == "1010":
				bstr += "A"
			elif input[a:a+4] == "1011":
				bstr += "B"
			elif input[a:a+4] == "1100":
				bstr += "C"
			elif input[a:a+4] == "1101":
				bstr += "D"
			elif input[a:a+4] == "1110":
				bstr += "E"
			elif input[a:a+4] == "1111":
				bstr += "F"
	return bstr


def main():
	#testbed = packet("D2FE28")
	#testbed = packet("38006F45291200")
	#testbed = packet("EE00D40C823060")

	#x = hex_to_bstr("8A004A801A8002F478")
	#testbed = packet(x)
	
	#x = hex_to_bstr("620080001611562C8802118E34")
	#testbed = packet(x)

	#x = hex_to_bstr("C0015000016115A2E0802F182340")
	#testbed = packet(x)

	#x = hex_to_bstr("A0016C880162017C3686B18A3D4780")
	#testbed = packet(x)

	# part one
	data = hex_to_bstr(open(str(sys.argv[1]), "r").read())
	testbed = packet(data)

	print(sum_of_version)

if __name__ == "__main__":
	main()
