#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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


typedef struct steps
{
	char step;
	vector<char> dependency;
	bool d_met;
} steps;


class day
{
	vector<steps> data;
	vector<string> raw_data;
public:
	day();
	string part1();
	//int part2();
	void gen_steps();
	vector<char> find_start_moves();
	char find_end();
	vector<char> find_p_moves(char);
	bool d_met(char, vector<steps>&);
	void elim_depend(char, vector<steps>&);
};

day::day() {
	aoc_input data_class("input");
	day::raw_data = data_class.vecstr();
}

void day::gen_steps()
{
	char q, w;
	for (auto &i: day::raw_data)
	{
		q = i.at(5);
		w = i.at(36);

		bool found = false;
		steps * ptr_v_s;
		for (auto &y: day::data)
		{
			if (y.step == w)
			{
				found = true;
				ptr_v_s = &y;
			}
		}

		if (found == true)
		{
			ptr_v_s->dependency.push_back(q);
		} else {
			steps tmp_step;
			tmp_step.step = w;
			tmp_step.dependency.push_back(q);
			tmp_step.d_met = false;
			day::data.push_back(tmp_step);
		}
	}
}

/* find the only char without a dependency */
vector<char> day::find_start_moves()
{
	vector<char> answer;
	vector<char> excluded = {};
	vector<char>::iterator it;
	vector<char>::iterator it_eb;

	/* fill excluded vector from i.step*/
	for (const auto &i: day::data)
	{
		it = find(excluded.begin(), excluded.end(), i.step);
		if (it == excluded.end())
			excluded.push_back(i.step);
	}

	/* find missing one */
	for (const auto &i: day::data)
	{
		for (const auto &q: i.dependency)
		{
			it = find(excluded.begin(), excluded.end(), q);
			if (it == excluded.end())
			{
				it_eb = find(answer.begin(), answer.end(), q);
				if (it_eb == answer.end())
					answer.push_back(q);
			}
		}
	}

	return answer;
}

char day::find_end()
{
	char answer;
	vector<char> excluded = {};
	vector<char>::iterator it;

	/* fill excluded vector from i.dependency */
	for (const auto &i: day::data)
	{
		for (const auto &q: i.dependency)
		{
			it = find(excluded.begin(), excluded.end(), q);
			if (it == excluded.end())
				excluded.push_back(q);
		}
	}

	/* find the last one left */
	for (const auto &i: day::data)
	{
		it = find(excluded.begin(), excluded.end(), i.step);
		if (it == excluded.end())
			answer = i.step;
	}

	return answer;
}

vector<char> day::find_p_moves(char head)
{
	vector<char> ret_a;
	vector<char>::iterator it;

	for (const auto &i: day::data)
	{
		vector<char> tmp = i.dependency;
		
		it = find(tmp.begin(), tmp.end(), head);
		if (it != tmp.end())
			ret_a.push_back(i.step);
	}

	return ret_a;
}

/* is a certain step's dependency met? */
bool day::d_met(char new_head, vector<steps> &raw_data)
{
	bool answer = true;

	for (const auto &i: raw_data)
	{
		if (i.step == new_head)
		{
			vector<char> tmp = i.dependency;
			if (tmp.size() != 0)
				answer = false;
		}
	}

	return answer;
}


void day::elim_depend(char head, vector<steps> &raw_data)
{
	vector<char>::iterator it;
	for (auto &i: raw_data)
	{
		vector<char> * tmp = &i.dependency;
		it = find(tmp->begin(), tmp->end(), head);
		if (it != tmp->end())
			tmp->erase(it);
	}
}

string day::part1()
{
	day::gen_steps();

	vector<steps> tmp_data = day::data;
	
	/* >1 entry with no dependency */
	vector<char> possible_moves = day::find_start_moves();
	char head = possible_moves.at(0);
	for (const auto &i: possible_moves)
		if (i < head)
			head = i;

	vector<char>::iterator pm_it;
	pm_it = find(possible_moves.begin(), possible_moves.end(), head);
	if (pm_it != possible_moves.end())
		possible_moves.erase(pm_it);


	char end = day::find_end();
	char new_head;
	string answer = "";
	
	bool running = true;

	while (1)
	{
		answer += head;

		if (head == end)
			break;

		// remove head as a dependency to allow new_head to be found
		day::elim_depend(head, tmp_data);

		// make sure possible_moves is filled
		if (possible_moves.size() == 0)
		{
			possible_moves = day::find_p_moves(head);
		} else
		{
			for (const auto &i: day::find_p_moves(head))
			{
				vector<char>::iterator pm_it = find(possible_moves.begin(), possible_moves.end(), i);
				if (pm_it == possible_moves.end())
					possible_moves.push_back(i);
			}
		}

		// find new_head
		vector<char> not_suitable = {};
		vector<char>::iterator ns_it;
		bool n_h_found = false;
		while (n_h_found == false)
		{
			//new candidate
			bool first_run = true;
			for (const auto &i: possible_moves)
			{
				ns_it = find(not_suitable.begin(), not_suitable.end(), i);
				if (ns_it != not_suitable.end())
				{
					continue;
				}
				else
				{
					if (first_run == true)
					{
						new_head = i;
						first_run = false;
					} else if (i < new_head)
						new_head = i;
				}

			}

			// are the candidate's dependencys met?
			if (day::d_met(new_head, tmp_data))
				n_h_found = true;
			else
				not_suitable.push_back(new_head);
			
		}

		// new_head found, now remove it from possible_moves
		vector<char>::iterator it;
		it = find(possible_moves.begin(), possible_moves.end(), new_head);
		possible_moves.erase(it);

		head = new_head;
	}

	return answer;
}


int main()
{
	day seven;
	cout << seven.part1() << endl;

	return 0;
}