#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

enum last_movement_t {LEFT, STRAIGHT, RIGHT};
enum direction_t {NORTH, EAST, SOUTH, WEST};
/*	driver struct
 *	contains unique id of driver as well as the driver's last action
*/
typedef struct driver {

	int id;
	pair<int, int> xy;
	last_movement_t last_movement;
	direction_t direction;
} driver;

pair<int, int> find_hw(vector<string> raw_vc)
{
	int width(raw_vc.at(0).length());
	int height(raw_vc.size());
	return (make_pair(height, width));
}

char* build_map_data(vector<string> raw_vc,  pair<int, int> hw)
{
	//cout<<"w:"<<width<<" h:"<<height<<endl;

	// build char map
	int x = 0;
	int y = 0;
	char *cmap = new char[hw.first * hw.second];

	for (const auto &i: raw_vc)
	{
		for (const auto &o: i)
		{
			cmap[(y * hw.second) + x] = o;
			x++;
		}
		y++;
		x = 0;
	}

return cmap;
}


vector<driver> find_drivers(char *cmap, pair<int, int> hw) 
{
	// keep points secured in a vector
	vector<driver> vdriver;
	int did = 0;

	int width = hw.second;
	int height = hw.first;

	// iterate over char map
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			char current_point = cmap[(y * width) + x];

			// is there currently a driver here?
			if ((current_point == '<') || (current_point == '>')
				|| (current_point == '^') || (current_point == 'v'))
			{
				driver cdriver;
				cdriver.last_movement = RIGHT;
				cdriver.xy = make_pair(x, y);
				cdriver.id = did;
				did++;

				if (current_point == '<')
				{
					cdriver.direction = WEST;
					cmap[(y * width) + x] = '-';
				}
				else if (current_point == '>')
				{
					cdriver.direction = EAST; 
					cmap[(y * width) + x] = '-';
				}
				else if (current_point == '^')
				{
					cdriver.direction = NORTH;
					cmap[(y * width) + x] = '|';
				}
				else if (current_point == 'v')
				{
					cdriver.direction = SOUTH;
					cmap[(y * width) + x] = '|';
				}

				vdriver.push_back(cdriver);
			}
		}

	//for (const auto &i: vdriver)
	//	cout<<i.id<<", x:"<<i.xy.first<<",y:"<<i.xy.second<<" direction:"<<i.direction<<endl;

	return vdriver;
}

bool check_id(int did, vector<int> vid)
{
	bool answer = false;
	for (const auto &i: vid)
		if (did == i)
			answer = true;

	return answer;
}

void remove_driver(int id, vector<driver> &drivers)
{
	vector<driver>::iterator vd_it;
	for (vd_it = drivers.begin(); vd_it != drivers.end(); ++vd_it)
		if ((*vd_it).id == id)
			break;

	drivers.erase(vd_it);
}

void find_next_moves(vector<driver> &drivers, char *cmap, pair<int, int> hw)
{

	//for (const auto &i: drivers)
	//	cout<<i.id<<", x:"<<i.xy.first<<",y:"<<i.xy.second<<" direction:"<<i.direction<<endl;
	
	vector<int> exclusion_v = {};
	for (int p = 0; p < hw.first; p++)
	{
		vector<int> to_remove;
		//cout<<p<<" ";
		for (auto &i: drivers)
		{
			if ((i.xy.second == p) && (check_id(i.id, exclusion_v) == false))
			{
				exclusion_v.push_back(i.id);

				pair<int, int> xy_current = i.xy;
				pair<int, int> xy_new;

				// Is driver on a '+'?
				if (cmap[(xy_current.second * hw.second) + xy_current.first] == '+')
				{
					if (i.last_movement == RIGHT)
					{
						i.last_movement = LEFT;

						if (i.direction == NORTH)
							i.direction = WEST;
						else if (i.direction == EAST)
							i.direction = NORTH;
						else if (i.direction == SOUTH)
							i.direction = EAST;
						else if (i.direction == WEST)
							i.direction = SOUTH;
					
					} else if (i.last_movement == LEFT)
					{
						i.last_movement = STRAIGHT;

					} else if (i.last_movement == STRAIGHT)
					{
						i.last_movement = RIGHT;

						if (i.direction == NORTH)
							i.direction = EAST;
						else if (i.direction == EAST)
							i.direction = SOUTH;
						else if (i.direction == SOUTH)
							i.direction = WEST;
						else if (i.direction == WEST)
							i.direction = NORTH;
					}
				}

				if (i.direction == SOUTH)
				{
					// Direction south of current position
					xy_new = make_pair(xy_current.first, xy_current.second + 1);
					// Update direction if need be
					if (cmap[(xy_new.second * hw.second) + xy_new.first] == '/')
						i.direction = WEST;
					else if (cmap[(xy_new.second * hw.second) + xy_new.first] == '\\')
						i.direction = EAST;

				} else if (i.direction == NORTH)
				{
					// Direction south of current position
					xy_new = make_pair(xy_current.first, xy_current.second - 1);
					// Update direction if need be
					if (cmap[(xy_new.second * hw.second) + xy_new.first] == '/')
						i.direction = EAST;
					else if (cmap[(xy_new.second * hw.second) + xy_new.first] == '\\')
						i.direction = WEST;

				} else if (i.direction == EAST)
				{
					// Direction south of current position
					xy_new = make_pair(xy_current.first + 1, xy_current.second);
					// Update direction if need be
					if (cmap[(xy_new.second * hw.second) + xy_new.first] == '/')
						i.direction = NORTH;
					else if (cmap[(xy_new.second * hw.second) + xy_new.first] == '\\')
						i.direction = SOUTH;

				} else if (i.direction == WEST)
				{
					// Direction south of current position
					xy_new = make_pair(xy_current.first - 1, xy_current.second);
					// Update direction if need be
					if (cmap[(xy_new.second * hw.second) + xy_new.first] == '/')
						i.direction = SOUTH;
					else if (cmap[(xy_new.second * hw.second) + xy_new.first] == '\\')
						i.direction = NORTH;
				}

				i.xy = xy_new;

				// Check for collisions
				to_remove = {};
				for (const auto &qq: drivers)
					for (const auto &ww: drivers)
						if (qq.id != ww.id)
							if (qq.xy == ww.xy)
							{
								cout<<"DING DING DING "<<qq.xy.first<<","<<qq.xy.second<<endl;
								to_remove.push_back(qq.id);
							}
			
				
			}
		}

		vector<int> removed;
		if (to_remove.size() > 0)
			for (const auto &i: to_remove)
			{
				bool found = false;
				for (const auto &p: removed)
					if (p == i)
						found = true;

				if (found == false)
					remove_driver(i, drivers);
			}

	}
}

int main()
{
	vector<string> raw_vc;
	ifstream file;
	file.open("input");
	if (!file)
	{
		cerr<<"Cannot open file"<<endl;
		return 1;
	}
	
	string str;
	while (getline(file, str))
		raw_vc.push_back(str);
	file.close();

	//for (const auto &i: raw_vc)
	//	cout<<i<<endl;
	pair<int, int> hw = find_hw(raw_vc);
	char *cmap = build_map_data(raw_vc, hw);
	vector<driver> drivers = find_drivers(cmap, hw);

	pair<int, int> answer;
	int count = 0;
	while(1)
	{
		find_next_moves(drivers, cmap, hw);
		
		if (drivers.size() == 1)
		{
			cout<<drivers.at(0).xy.first<<","<<drivers.at(0).xy.second<<endl;
			break;
		}

		count++;
	}

	delete cmap;

	return 0;
}
