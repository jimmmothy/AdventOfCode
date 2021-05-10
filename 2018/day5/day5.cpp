#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class aoc_input 
{
	string filename;
	ifstream aoc_file;
public:
	aoc_input(string x) : filename(x) {};
	bool open_file();
	string str(void);
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

string aoc_input::str(void) 
{
	string tmp;

	if (!aoc_input::open_file())
		return tmp;

	string str;
	while (getline(aoc_input::aoc_file, str)) {
		if (str.size() > 0)
			tmp += str;
	}

	aoc_input::aoc_file.close();
	return tmp;
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/

class day
{
	string data;
public:
	day();
	int part1();
	int part2();
	string reduce_polymer(string);
	vector<string> gen_v_input(string);
	char polar_c(char);
};

day::day() {
	aoc_input data_class("input");
	data = data_class.str();
}

/* accept char, return what the polar opposite should be, i.e. a -> A, B -> b */
char day::polar_c(char r_input)
{
	char tmp;
	if (islower(r_input))
	{
		tmp = toupper(r_input);
	} else if (isupper(r_input))
	{
		tmp=tolower(r_input);
	}

	return tmp;
}


/* Fixed this up to be a lot more efficient, without calling string::erase a billion times */
string day::reduce_polymer(string r_input)
{
	string s_input = r_input;
	string s_answer;

	char current;
	char next;
	bool lopf;
	bool found_one = true;

	string::iterator it;
	while (found_one == true)
	{
		found_one = false;
		s_answer = "";

		for (it = s_input.begin(); it < s_input.end()-1; it++)
		{
			current = *it;
			next = day::polar_c(current);

			if (*(it + 1) != next)
			{
				s_answer += *it;
				lopf = false;
			} else {
				it++;
				lopf = true;
				found_one = true;
			}
		}

		if (lopf == false)
		{
			s_answer += s_input.at(s_input.length()-1);
		}
		s_input = s_answer;
	}

	return s_answer;
}

vector<string> day::gen_v_input(string r_input)
{
	vector<string> ret_tmp;
	string s_tmp;

	for (int x = 97; x < 123; x++)
	{
		s_tmp = "";
		for (const auto &i: r_input)
		{
			if ((i != x) && (i != day::polar_c(x)))
				s_tmp += i;
		}

		ret_tmp.push_back(s_tmp);
	}
	return ret_tmp;
}

int day::part1()
{
	string answer = day::reduce_polymer(day::data);
	return answer.size();
}

int day::part2()
{	vector<string> v_input;
	v_input = day::gen_v_input(day::data);

	int tmp_answer = 999999;
	int counter = 0;
	for (const auto &i: v_input)
	{
		string tmp_s = day::reduce_polymer(i);
		if (tmp_s.size() < tmp_answer)
			tmp_answer = tmp_s.size();
	}

	return tmp_answer;
}

int main()
{
	day five;
	cout<<five.part1()<<endl;
	cout<<five.part2()<<endl;

	return 0;
}