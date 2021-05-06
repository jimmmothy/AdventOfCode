
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class aoc_input 
{
	string filename;
	ifstream aoc_file;
public:
	aoc_input(string x) : filename(x) {};
	bool open_file();
	vector<string> str_vec(void);
};

bool aoc_input::open_file()
{
	aoc_input::aoc_file.open((aoc_input::filename));
	if (!aoc_input::aoc_file) {
		cerr << "Cannot open file:"<<aoc_input::filename<<endl;
		return false;
	}
	
	return true;
}

vector<string> aoc_input::str_vec(void) 
{
	vector<string> tmp;

	if (!aoc_input::open_file())
		return tmp;

	string str;
	while (getline(aoc_input::aoc_file, str)) {
		if (str.size() > 0)
			tmp.push_back(str);
	}

	aoc_input::aoc_file.close();
	return tmp;
}

class day
{
	vector<string> data;
public:
	day();
	int part1();
	int part2();
};

day::day() {
	aoc_input data_class("input");
	data = data_class.str_vec();
}

int day::part1() {

	int answer = 0;
	char op;
	int value;
	string tmp_line;
	string tmp;

	for (int x = 0; x < day::data.size(); x++) {
		tmp = "";
		tmp_line = day::data.at(x);
		op = tmp_line.at(0);

		for (int y = 1; y < tmp_line.length(); y++) {
			tmp += tmp_line.at(y);
		}
		value = (int)stoi(tmp);
		
		if (op == '+')
			answer += value;

		if (op == '-')
			answer -= value;
	}
	return answer;
}

int day::part2() {

	int answer = 0;
	char op;
	int value;
	string tmp_line;
	string tmp;
	vector<int> frequencies;

	while(1) {

		for (int x = 0; x < day::data.size(); x++) {

			frequencies.insert(upper_bound(frequencies.begin(), frequencies.end(), answer), answer);

			tmp = "";
			tmp_line = day::data.at(x);
			op = tmp_line.at(0);

			for (int y = 1; y < tmp_line.length(); y++)
				tmp += tmp_line.at(y);
			
			value = (long)stoi(tmp);
			
			if (op == '+')
				answer += value;
			else if (op == '-')
				answer -= value;

			if (binary_search(frequencies.begin(), frequencies.end(), answer) == true)
				return answer;
		}
	}
	return 0;	
}

int main() {
	
	day one;

	cout << one.part1() << endl;
	cout << one.part2() << endl;

	return 0;
}