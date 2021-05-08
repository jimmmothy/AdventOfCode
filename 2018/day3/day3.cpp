#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

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

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/

typedef struct claim
{
	int id;
	int x;
	int y;
	int width;
	int height;
	string original;
} claim;

class day
{
	vector<string> data;
public:
	day();
	int part1();
	int part2();
	claim gen_claim(string);
};

day::day() {
	aoc_input data_class("input");
	data = data_class.str_vec();
}



claim day::gen_claim(string r_input)
{
	regex claim_re ("[#]([0-9]+)[ @]+([0-9]+)[,]([0-9]+)[: ]+([0-9]+)[x]([0-9]+)");
	smatch sm;
	regex_match(r_input, sm, claim_re);

	claim tmp;
	tmp.id = stoi(sm[1]);
	tmp.x = stoi(sm[2]);
	tmp.y = stoi(sm[3]);
	tmp.width = stoi(sm[4]);
	tmp.height = stoi(sm[5]);
	tmp.original = r_input;

	return tmp;
}


int day::part1()
{
	vector<claim> claim_data;
	for (auto x: day::data)
	{
		claim_data.push_back(day::gen_claim(x));
	}

	int f_wid = 0;
	int f_hgt = 0;
	int c_wid;
	int c_hgt;

	for (auto z: claim_data)
	{
		c_wid = z.x + z.width;
		c_hgt = z.y + z.height;

		if (c_wid > f_wid)
			f_wid = c_wid;

		if (c_hgt > f_hgt)
			f_hgt = c_hgt;
	}

	int fabric[f_wid][f_hgt];
	for (int x = 0; x < f_wid; x++)
		for (int y = 0; y < f_hgt; y++)
			fabric[x][y] = 0;

	for (auto z: claim_data)
	{
		for (int x = z.x; x < (z.x + z.width); x++)
		{
			for (int y = z.y; y < (z.y + z.height); y++)
			{
				fabric[x][y] += 1;	
			}
		}
	}

	int counter = 0;
	for (int x = 0; x < f_wid; x++)
		for (int y = 0; y < f_hgt; y++)
			if (fabric[x][y] > 1)
				counter++;

	return counter;
}

int day::part2()
{
	vector<claim> claim_data;
	for (auto x: day::data)
	{
		claim_data.push_back(day::gen_claim(x));
	}

	int f_wid = 0;
	int f_hgt = 0;
	int c_wid;
	int c_hgt;

	for (auto z: claim_data)
	{
		c_wid = z.x + z.width;
		c_hgt = z.y + z.height;

		if (c_wid > f_wid)
			f_wid = c_wid;

		if (c_hgt > f_hgt)
			f_hgt = c_hgt;
	}

	int fabric[f_wid][f_hgt];
	for (int x = 0; x < f_wid; x++)
		for (int y = 0; y < f_hgt; y++)
			fabric[x][y] = 0;

	for (auto z: claim_data)
	{
		for (int x = z.x; x < (z.x + z.width); x++)
		{
			for (int y = z.y; y < (z.y + z.height); y++)
			{
				if (fabric[x][y] == 0)
				{
					fabric[x][y] = z.id;
				} else {
					fabric[x][y] = 1402;
				}
			}
		}
	}

	bool overlap;
	int answer = 0;
	for (auto z: claim_data)
	{
		overlap = false;
		for (int x = z.x; (x < z.x + z.width) && (overlap == false); x++)
		{
			for (int y = z.y; (y < z.y + z.height) && (overlap == false); y++)
			{
				if (fabric[x][y] == 1402)
					overlap = true;
			}
		}

		if (overlap == false)
		{
			answer = z.id;
			break;
		}
	}

	return answer;
}


int main()
{
	day three;
	cout << three.part1() << endl;
	cout << three.part2() << endl;

	return 0;
}