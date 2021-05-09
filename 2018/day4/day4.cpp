#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <ctime>
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

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/

enum action_t {START, SLEEP, WAKE};

typedef struct log
{
	time_t timestamp;
	int guard;
	action_t action;
	string original;
} log;

typedef struct guard_log
{
	int guard;
	int min_asleep;
	vector<pair<int, int>> minutes;
} guard_log;

class day
{
	vector<string> data;
	guard_log * ptr_g_l;
public:
	day();
	int part1();
	int part2();
	log parse_log(string);
};

day::day() {
	aoc_input data_class("input");
	data = data_class.str_vec();
}

log day::parse_log(string r_input)
{
	regex claim_re ("[\\[](\\d+)[-](\\d+)[-](\\d+)[ ](\\d+)[:](\\d+)[\\] ] (Guard #(\\d+) begins shift|falls asleep|wakes up)");
	smatch sm;
	regex_match(r_input, sm, claim_re);

	log tmp;

	time_t rawtime;
	time(&rawtime);
	
	struct tm * tmp_time;
	tmp_time  = localtime(&rawtime);

	tmp_time->tm_sec = 0;
	tmp_time->tm_min = stoi(sm[5]);
	tmp_time->tm_hour = stoi(sm[4]);
	tmp_time->tm_mday = stoi(sm[3]);
	tmp_time->tm_mon = stoi(sm[2]) - 1;
	tmp_time->tm_year = stoi(sm[1]) - 1900;
	
	tmp.timestamp = mktime(tmp_time);

	string tmp6 = sm[6];

	if (tmp6.at(0) == 'G') {
		tmp.guard = stoi(sm[7]);
		tmp.action = START;
	} else if (tmp6.at(0) == 'f') {
		tmp.guard = 0;
		tmp.action = SLEEP;
	} else if (tmp6.at(0) == 'w') {
		tmp.guard = 0;
		tmp.action = WAKE;
	}

	tmp.original = r_input;

	return tmp;
}

int day::part1()
{
	vector<log> full_log;
	log tmp_log;
	int tmp_guard;
	for (const auto &x: day::data) {
		tmp_log = day::parse_log(x);

		int pos = 0;
		int pos_it = 1;
		for (const auto &x: full_log)
		{
			if (tmp_log.timestamp > x.timestamp)
				pos = pos_it;
			pos_it++;
		}

		vector<log>::iterator it;
		it = full_log.begin() + pos;
		full_log.insert(it, tmp_log);
	}

	vector<guard_log> truth;
	bool found_guard;
	time_t tmp_sleep;
	struct tm * tmp_t_sleep;
	int time_asleep;
	int time_awake;
	double diff;
	int current_guard;

	for (const auto &x: full_log)
	{

		if (x.action == START) 
		{
			/* does the guard exist? */
			found_guard = false;
			for (auto i: truth)
				if (i.guard == x.guard)
					found_guard = true;

			/* add guard */
			if (found_guard == false)
			{
				guard_log tmp_guard_log;
				tmp_guard_log.guard = x.guard;
				tmp_guard_log.min_asleep = 0;
				truth.push_back(tmp_guard_log);
			}

			/* generate pointer to guard */
			for (auto &i: truth)
			{
				if (i.guard == x.guard)
					day::ptr_g_l = &i;
			}

			current_guard = x.guard;
		
		} else if (x.action == SLEEP)
		{
			tmp_sleep = x.timestamp;
			tmp_t_sleep = localtime(&tmp_sleep);
			time_asleep = tmp_t_sleep->tm_min;

		} else if (x.action == WAKE)
		{
			diff = (difftime(x.timestamp, tmp_sleep) / 60);

			/* make a pointer to the right vector element of our guard log*/
			for (auto &p: truth)
				if (p.guard == x.guard)
					day::ptr_g_l = &p;

			/* go through every minute between tmp_sleep...n(diff) and update truth */

			for (int q = time_asleep; q < (time_asleep + diff); q++)
			{
				/* mod out minutes to 0-59 */
				int w;
				if (q > 59)
					w = q % 60;
				else
					w = q;

				/* add to total guard minutes / maybe just inc by diff instead? */
				day::ptr_g_l->min_asleep++;

				/* if minute exists in the vector of pairs, increment it, otherwise add */
				bool min_found = false;
				for (auto &i: day::ptr_g_l->minutes)
				{
					if (i.first == w)
					{
						i.second++;
						min_found = true;
					}
				}

				if (min_found == false)
					day::ptr_g_l->minutes.push_back(make_pair(w, 1));

			}
		}
	}

	/* full log processed, 

	   find guard w/ most sleep*/
	int tmp_mins = 0;
	for (auto &i: truth)
	{
		if (i.min_asleep > tmp_mins)
		{
			tmp_mins = i.min_asleep;
			day::ptr_g_l = &i;
		}
	}

	/* find the minute most spent asleep */
	int tmp_min = 0;
	int tmp_min_v = 0;
	for (const auto &i: day::ptr_g_l->minutes)
	{
		if (i.second > tmp_min_v) {
			tmp_min = i.first;
			tmp_min_v = i.second;
		}
	}
	int answer_guard = day::ptr_g_l->guard;

	return (answer_guard * tmp_min);
}

int day::part2()
{
	vector<log> full_log;
	log tmp_log;
	int tmp_guard;
	for (const auto &x: day::data) {
		tmp_log = day::parse_log(x);

		int pos = 0;
		int pos_it = 1;
		for (const auto &x: full_log)
		{
			if (tmp_log.timestamp > x.timestamp)
				pos = pos_it;
			pos_it++;
		}

		vector<log>::iterator it;
		it = full_log.begin() + pos;
		full_log.insert(it, tmp_log);
	}

	vector<guard_log> truth;
	bool found_guard;
	time_t tmp_sleep;
	struct tm * tmp_t_sleep;
	int time_asleep;
	int time_awake;
	double diff;
	int current_guard;

	for (const auto &x: full_log)
	{

		if (x.action == START) 
		{
			/* does the guard exist? */
			found_guard = false;
			for (auto i: truth)
				if (i.guard == x.guard)
					found_guard = true;

			/* add guard */
			if (found_guard == false)
			{
				guard_log tmp_guard_log;
				tmp_guard_log.guard = x.guard;
				tmp_guard_log.min_asleep = 0;
				truth.push_back(tmp_guard_log);
			}

			/* generate pointer to guard */
			for (auto &i: truth)
			{
				if (i.guard == x.guard)
					day::ptr_g_l = &i;
			}

			current_guard = x.guard;
		
		} else if (x.action == SLEEP)
		{
			tmp_sleep = x.timestamp;
			tmp_t_sleep = localtime(&tmp_sleep);
			time_asleep = tmp_t_sleep->tm_min;

		} else if (x.action == WAKE)
		{
			diff = (difftime(x.timestamp, tmp_sleep) / 60);

			/* make a pointer to the right vector element of our guard log*/
			for (auto &p: truth)
				if (p.guard == x.guard)
					day::ptr_g_l = &p;

			/* go through every minute between tmp_sleep...n(diff) and update truth */

			for (int q = time_asleep; q < (time_asleep + diff); q++)
			{
				/* mod out minutes to 0-59 */
				int w;
				if (q > 59)
					w = q % 60;
				else
					w = q;

				/* add to total guard minutes / maybe just inc by diff instead? */
				day::ptr_g_l->min_asleep++;

				/* if minute exists in the vector of pairs, increment it, otherwise add */
				bool min_found = false;
				for (auto &i: day::ptr_g_l->minutes)
				{
					if (i.first == w)
					{
						i.second++;
						min_found = true;
					}
				}

				if (min_found == false)
					day::ptr_g_l->minutes.push_back(make_pair(w, 1));

			}
		}
	}

	int a_guard = 0;
	int a_min = 0;
	int a_min_v = 0;
	bool new_winner;

	for (const auto x: truth)
	{
		new_winner = false;

		for (const auto y: x.minutes)
		{
			if (y.second > a_min_v)
			{
				a_min = y.first;
				a_min_v = y.second;
				new_winner = true;
			}
		}
		if (new_winner == true)
			a_guard = x.guard;
	}

	return (a_guard * a_min);
}


int main()
{
	day four;
	cout << four.part1() << endl;
	cout << four.part2() << endl;

	return 0;
}