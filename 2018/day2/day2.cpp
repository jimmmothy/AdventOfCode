#include <fstream>
#include <iostream>
#include <vector>
#include <string>

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
	string part2();
};

day::day() {
	aoc_input data_class("input");
	data = data_class.str_vec();
}

int day::part1()
{
	vector<pair<char, int>> dict;
	string tmp_line;
	char curr_let;
	bool let_found;
	int two_count = 0;
	int three_count = 0;

	bool found_two;
	bool found_three;

	vector<string>::iterator myvec;
	string::iterator mystr;
	
	for (myvec = day::data.begin(); myvec != day::data.end(); ++myvec)
	{
		tmp_line = *myvec;
		dict.clear();

		for (mystr = tmp_line.begin(); mystr != tmp_line.end(); ++mystr)
		{
			let_found = false;
			curr_let = *mystr;

			/* note: passing vector by reference, not value */
			for (pair<char, int>& i : dict)
			{
				if (i.first == curr_let)
				{
					i.second += 1;
					let_found = true;
					break;
				}
			}

			if (let_found == false)
			{
				dict.push_back(make_pair(curr_let, 1));
			}
		}

		found_two = false;
		found_three = false;
		for (pair<char, int>& i : dict)
		{
			if (i.second == 2 && found_two == false)
			{
				two_count++;
				found_two = true;
			} else if (i.second == 3 && found_three == false)
			{
				three_count++;
				found_three = true;
			}
		}
	}
	//cout<<"Twos:"<<two_count<<". Threes:"<<three_count<<endl;
	return (two_count * three_count);
}


string day::part2()
{
	int x;
	int y;
	int y_offset = 1;
	int lines = day::data.size();
	int counter;
	int counter_index;
	string answer;
	bool answer_found = false;

	for (x = 0; (x < lines-1 && answer_found == false); x++)
	{
		for (y = y_offset; (y < lines && answer_found == false); y++)
		{
			string string_one = day::data.at(x);
			string string_two = day::data.at(y);
			counter = 0;
			counter_index = 0;

			for (int z = 0; (z < string_one.length() && counter <= 1); z++)
			{
				if (string_one.at(z) != string_two.at(z))
				{
					counter++;
					counter_index = z;
				}
			}

			if (counter == 1)
			{
				answer_found = true;
				for (int z = 0; z < string_one.length(); z++)
				{
					if (z != counter_index)
						answer += string_one.at(z);
				}
			}
		}
		y_offset++;
	}
	return answer;
}

int main()
{
	day two;
	cout << two.part1() << endl;
	cout << two.part2() << endl;

	return 0;
}