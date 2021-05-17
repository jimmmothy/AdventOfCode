#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <cmath>

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

typedef struct point
{
	int posx;
	int posy;
	int velx;
	int vely;
} point;

typedef struct point_d
{
	int dx, dy;
	int ux, uy, lx, ly;
	int offx, offy;
	int sizex, sizey;
} point_d;

enum direction_t {FORWARD, BACKWARD};

class day
{
	vector<string> raw_data;
	vector<point> data;
public:
	day();
	int part1();
	point parse_data(string);
	vector<point> gen_data(vector<string>);
	void step_point(point*, direction_t);
	void one_second_move(direction_t);
	point_d delta_calc();
};

day::day()
{
	aoc_input data_class("input");
	raw_data = data_class.str_vec();
}

point day::parse_data(string r_input)
{
	regex claim_re ("[position=<\\ ]+([-0-9]+)[,\\ ]+([-0-9]+)[>\\ velocity=<]+([-0-9]+)[,\\ ]+([-0-9]+)[>]");
	smatch sm;
	regex_match(r_input, sm, claim_re);

	point tmp;
	tmp.posx = stoi(sm[1]);
	tmp.posy = stoi(sm[2]);
	tmp.velx = stoi(sm[3]);
	tmp.vely = stoi(sm[4]);

	return tmp;
}

vector<point> day::gen_data(vector<string> input)
{
	vector<point> tmp_vp;
	point tmp_p;
	for (const auto &i: input)
	{
		tmp_p = day::parse_data(i);
		tmp_vp.push_back(tmp_p);
	}
	return tmp_vp;
}

void day::step_point(point *input, direction_t direction)
{
	if (direction == FORWARD)
	{
		input->posx += input->velx;
		input->posy += input->vely;
	} else if (direction == BACKWARD)
	{
		input->posx -= input->velx;
		input->posy -= input->vely;
	}
}

void day::one_second_move(direction_t direction)
{
	point *tmp;
	for (auto &i: day::data)
	{
		tmp = &i;
		day::step_point(tmp, direction);
	}
}

point_d day::delta_calc(void)
{
	point_d ret_a;

	int ux = 0, lx = 0, uy = 0, ly = 0;
	for (const auto &i: day::data)
	{
		if (i.posx > ux)
			ux = i.posx;
		else if (i.posx < lx)
			lx = i.posx;
		if (i.posy > uy)
			uy = i.posy;
		else if (i.posy < ly)
			ly = i.posy;
	}

	ret_a.ux = ux;
	ret_a.lx = lx;

	ret_a.uy = uy;
	ret_a.ly = ly;

	ret_a.dx = abs(ux - lx);
	ret_a.dy = abs(uy - ly);

	int offset = 2;
	if (lx < 0)
		ret_a.offx = abs(lx) + offset;
	else
		ret_a.offx = offset;

	if (ly < 0)
		ret_a.offy = abs(ly) + offset;
	else
		ret_a.offy = offset;

	ret_a.sizex = ret_a.dx + ret_a.offx + offset;
	ret_a.sizey = ret_a.dy + ret_a.offy + offset;
	
	return ret_a;
}

int day::part1()
{
	day::data = day::gen_data(day::raw_data);
	point_d deltas = day::delta_calc();

	bool first = true;
	int deltay_curr, deltay_prev;
	point_d tmp = deltas;
	int it_count = 0;

	while (++it_count)
	{
		cout<<it_count<<endl;
		// copy original vector and details
		vector<point> tmp_d = day::data;
		point_d tmp_p = tmp;
		
		// move original forward 1 sec
		day::one_second_move(FORWARD);
		tmp = day::delta_calc();

		if (first == true)
		{
			first = false;
			deltay_curr = tmp.dy;
			deltay_prev = tmp.dy;
		} else {
			deltay_curr = tmp.dy;
		}

		// Answer found on on tmp_d
		if (deltay_prev < deltay_curr)
		{
			for (const auto &i: tmp_d)
				cout<<i.posx<<" "<<i.posy<<endl;

			// allocate array for output
			//char *array = new char[(tmp_p.dy + tmp_p.offy) * (tmp_p.dx + tmp_p.offx)];
			char *array = new char[tmp_p.sizex * tmp_p.sizey];

			// fill with '.'
			for (int x = 0; x < tmp_p.sizex; x++)
				for (int y = 0; y < tmp_p.sizey; y++)
					array[(tmp_p.sizex * y) + x] = '.';

			// add star points
			for (const auto &i: tmp_d)
				array[(i.posy * tmp_p.sizex) + (tmp_p.offy * tmp_p.sizex) + (i.posx + tmp_p.offx) ] = '#';

			

			// print output
			for (int y = 0; y < tmp_p.sizey; y++)
			{
				for (int x = 0; x < tmp_p.sizex; x++)
					cout<<array[(tmp_p.sizex * y) + x];
				cout<<endl;
			}
		
			delete[] array;
			break;
		}
		deltay_prev = deltay_curr;
	}

	return (it_count - 1);
}

int main()
{
	day ten;
	cout<<ten.part1()<<endl;

	return 0;
}