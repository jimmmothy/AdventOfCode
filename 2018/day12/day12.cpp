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
	vector<string> vecstr(void);
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

vector<string> aoc_input::vecstr(void) 
{
	vector<string> tmp_vc;

	if (!aoc_input::open_file())
		return tmp_vc;

	string str;
	while (getline(aoc_input::aoc_file, str))
		if (str.size() > 0)
			tmp_vc.push_back(str);

	aoc_input::aoc_file.close();

	return tmp_vc;
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/


void topntail(vector<pair<int, char>> *field, int ammount)
{
	// tail
	int count = 0;
	for (const auto &i: *field)
		if (i.second == '.')
			count++;
		else
			break;

	if (count <= ammount)
	{
		vector<pair<int, char>>::iterator vp_it;
		int start_id = field->at(0).first - 1;

		for (int x = 0; x < (ammount - count); x++, start_id--)
		{
			vp_it = field->begin();
			field->insert(vp_it, make_pair(start_id, '.'));
		}
	}

	//top
	count = 0;
	for (int x = 0; x < ammount; x++)
		if (field->at(field->size() - x - 1).second == '.')
			count++;
		else
			break;


	if (count <= ammount)
	{
		vector<pair<int, char>>::iterator vp_it;
		int start_id = field->at(field->size() - 1).first + 1;

		for (int x = 0; x < (ammount - count); x++, start_id++)
		{
			vp_it = field->end();
			field->insert(vp_it, make_pair(start_id, '.'));
		}
	}
}

vector<pair<int, char>> find_changes(vector<pair<int, char>> field, vector<pair<char, string>> spread)
{
	int length = 5;
	vector<pair<int, char>> changes;

	// loop through all inputs
	for (const auto &i: spread)
	{
		vector<pair<int, char>>::iterator vp_it;
		
		// iterate over every possible 5 char string
		for (vp_it = field.begin(); vp_it != field.end() - length; vp_it++)
		{
			string tmp = "";
			for (int x = 0; x < length; x++)
				tmp += (vp_it + x)->second;

			if (tmp == i.second)
			{
				pair<int, char> new_change;
				new_change = make_pair((vp_it + 2)->first, i.first);
				changes.push_back(new_change);
			}
		}
	}
	return changes;
}

vector<pair<int, char>> new_generation(vector<pair<int, char>> changes)
{
	// find the lowest and highest id to make a range
	int low, high;
	bool first = true;
	for (const auto &i: changes)
		if (first == true)
		{
			low = i.first;
			high = i.first;
			first = false;
		} else if (i.first < low) {
			low = i.first;
		} else if (i.first > high) {
			high = i.first;
		}

	// fill an empty vector with .s
	vector<pair<int, char>> new_field;
	for (int x = low; x <= high; x++)
		new_field.push_back(make_pair(x, '.'));

	// apply changes to new field
	for (const auto &i: changes)
		for (auto &p: new_field)
			if (p.first == i.first)
			{
				p.second = i.second;
				break;
			}
	return new_field;
}


long doTheNeedfull(vector<pair<int, char>> o_field, vector<pair<char, string>> o_spread, long generations_max, bool part_two)
{
	vector<pair<int, char>> field = o_field;
	vector<pair<char, string>> spread = o_spread;
	int generations = 0;
	int delta = 0;
	int prev_length = 0;

	while (generations < generations_max)
	{
		// make sure vector has at least 3 .s on both sides
		topntail(&field, 5);

		if (part_two == true)
		{
			//for (const auto &i: *field)
			//	cout<<i.second;

			int length = 0;
			for (const auto &i: field)
				if (i.second == '#')
					length += i.first;

			//cout<<generations<<": "<<length<<" delta:"<<(length-delta)<<endl;
			delta = (length-prev_length);
			prev_length = length;
		}

		// work out the changes that need to occur on next generation
		vector<pair<int, char>> changes;
		changes = find_changes(field, spread);

		// build a new field
		vector<pair<int, char>> new_field;
		new_field = new_generation(changes);
		field = new_field;

		generations++;		
	}

	long answer = 0;
	for (const auto &i: field)
		if (i.second == '#')
			answer += i.first;

	if (part_two == true)
		answer += ((50000000000 - generations_max) * delta);

	return answer;
}


int main()
{
	aoc_input raw_input_class("input");
	vector<string> raw_input = raw_input_class.vecstr();

	// Create the initial playing field
	int id = 0;
	vector<pair<int, char>> field;
	string tmp = raw_input.at(0);
	string::iterator s_it;
	for (s_it = tmp.begin(); s_it != tmp.end(); s_it++)
		if ((*s_it == '#') || (*s_it == '.'))
		{
			field.push_back(make_pair(id, *s_it));
			id++;
		}
	raw_input.erase(raw_input.begin());

	// Calculate a vector of all changes
	vector<pair<char, string>> spread;
	tmp = "";
	int count = 0;
	char action;
	for (const auto &i: raw_input)
	{
		for (const auto &u: i)
		{
			if (count < 5)
				tmp += u;
			else if (count == 9)
				action = u;
			count++;
		}
		spread.push_back(make_pair(action, tmp));
		tmp = "";
		count = 0;
	}

	cout<<doTheNeedfull(field, spread, 20, false)<<endl;
	cout<<doTheNeedfull(field, spread, 2000, true)<<endl;

	return 0;
}