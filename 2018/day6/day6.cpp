#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

typedef struct g_data
{
	int id, x, y;
} g_data;

class aoc_input 
{
	string filename;
	ifstream aoc_file;
public:
	aoc_input(string x) : filename(x) {};
	bool open_file();
	vector<g_data> vecp(void);
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

vector<g_data> aoc_input::vecp(void) 
{
	vector<g_data> vtmp;
	int counter = 1;

	if (!aoc_input::open_file())
		return vtmp;

	string str;
	regex re ("(\\d+)[\\,\\ ]+(\\d+)");
	smatch sm;
	while (getline(aoc_input::aoc_file, str)) {
		if (str.size() > 0)
		{
			regex_match(str, sm, re);
			g_data tmp;
			tmp.x = stoi(sm[1]);
			tmp.y = stoi(sm[2]);
			tmp.id = counter;
			vtmp.push_back(tmp);
			counter++;
		}
	}

	aoc_input::aoc_file.close();
	return vtmp;
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/


class day
{
	vector<g_data> data;
	vector<int> excluded;
	vector<int> included;
	int grid_array[999][999];
	int gx;
	int gy;
public:
	day();
	int part1();
	int part2();
	int m_id(int, int);
	void exclude_id(int);
	void include_id(void);
	int count_id(int);
	int m_val(int, int, int, int);
};

day::day()
{
	aoc_input data_class("input");
	day::data = data_class.vecp();
	day::gx = 0;
	day::gy = 0;
}

int day::m_id(int x, int y)
{
	int tmp;
	int dx, dy, mv, id;
	bool first = true;
	bool no_md = false;
	for (const auto &i: day::data)
	{
		dx = abs(x - i.x);
		dy = abs(y - i.y);
		mv = dx + dy;

		//cout<<"x:"<<x<<",y:"<<y<<" i.x:"<<i.x<<",i.y:"<<i.y<<" mv:"<<mv<<endl;

		if (first == true)
		{
			tmp = mv;
			first = false;
			id = i.id;
		} else if (mv < tmp)
		{
			no_md = false;
			tmp = mv;
			id = i.id;
		} else if (tmp == mv)
		{
			no_md = true;
		}
	}

	if (no_md == true)
		id = 0;

	//cout<<"M Distance ID for "<<x<<","<<y<<":"<<id<<endl;

	return id;
}

void day::exclude_id(int num)
{
	if (num != 0)
	{
		bool found = false;
		for (const auto &i: day::excluded)
		{
			if (i == num)
			{
				found = true;
				break;
			}
		}
		if (found == false)
			day::excluded.push_back(num);
	}
}

void day::include_id(void)
{
	for (const auto &q: day::data)
	{
		bool found = false;
		for (const auto &i: day::excluded)
		{
			if (q.id == i)
				found = true;
		}

		if (found == false)
			day::included.push_back(q.id);
	}
}

int day::count_id(int num)
{
	int tmp_count = 0;
	for (int x = 0; x < day::gx; x++)
		for (int y = 0; y < day::gy; y++)
			if (day::grid_array[x][y] == num)
					tmp_count++;

	//cout<<"Counting:"<<num<<". Value:"<<tmp_count<<endl;

	return tmp_count;
}

int day::m_val(int x1, int y1, int x2, int y2)
{
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	return dx + dy;
}

int day::part1()
{
	/* find the bounds for char array */
	for (const auto &i: day::data)
	{
		if (i.x > day::gx)
			day::gx = i.x;
		if (i.y > day::gy)
			day::gy = i.y;
	}
	day::gx++;
	day::gy++;

	/* iterate through every item of grid
	   calculate the manhattan distance to each vector in data
	   the shorted one gets tagged with the ID of that vector */

	for (int x = 0; x < day::gx; x++)
		for (int y = 0; y < day::gy; y++)
			day::grid_array[x][y] = day::m_id(x, y);

	/* exclude edges */
	for (int x = 0; x < day::gx; x++)
	{
		day::exclude_id(day::grid_array[x][0]);
		day::exclude_id(day::grid_array[x][day::gy - 1]);
	}
	for (int y = 0; y < gy; y++)
	{
		day::exclude_id(day::grid_array[0][y]);
		day::exclude_id(day::grid_array[day::gx - 1][y]);
	}

	/* cycle through non excluded IDs, send to day::count_id to find how large they are */
	day::include_id();
	int tmp_count;
	int tmp_answer;
	bool first = true;
	for (const auto &i: day::included)
	{
		tmp_count = day::count_id(i);

		if (first == true)
		{
			tmp_answer = tmp_count;
			first = false;
		} else {
			if (tmp_count > tmp_answer)
				tmp_answer = tmp_count;
		}

	}

	return tmp_answer;
}

int day::part2()
{
	/* assume day::data and day::grid_array is already filled by day1 */

	/* give number 1000 to grid_array that contains a co-ordinate 
	   numbers that satisfy sum of m_dis 32, will be marked 1001  */
	for (const auto &i: day::data)
		day::grid_array[i.x][i.y] = 1000;

	/* Iterate through every grid entry */
	int tmp_mv;
	int tmp_v;
	for (int x = 0; x < day::gx; x++)
	{
		for (int y = 0; y < day::gy; y++)
		{
			/* fill tmp_mv w/ aggregate manhattan values */
			tmp_mv = 0;
			for (const auto &p: day::data)
			{
				tmp_v = day::m_val(x, y, p.x, p.y);
				tmp_mv += tmp_v;
				if (tmp_mv >= 10000)
					break;
			}
			if (tmp_mv < 10000)
				day::grid_array[x][y] = 1001;
		}
	}

	/* count areas that satify */
	int answer = day::count_id(1001);

	return answer;
}

int main()
{
	day six;
	cout<<six.part1()<<endl;
	cout<<six.part2()<<endl;

	return 0;
}