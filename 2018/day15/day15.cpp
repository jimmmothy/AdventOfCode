#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <queue>
#include <cstring>

using namespace std;

/* 
	handle file i/o
*/

char* grab_input(string filename, int &height, int &width)
{
	vector<string> input_vs;
	ifstream my_file;
	my_file.open(filename);
	if (!my_file)
	{
		cerr<<"Cannot open file, error!!"<<endl;
		return NULL;
	}

	string str;
	while (getline(my_file, str))
	{
		if (str.size() > 0)
			input_vs.push_back(str);
	}

	my_file.close();

	width = input_vs.at(0).length();
	height = input_vs.size();

	string whole_input;
	for (const auto &i: input_vs)
		whole_input += i;

	char *return_grid = new char[width * height];
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			return_grid[(width * y) + x] = whole_input[(width * y) + x];

	return return_grid;
}

/*
	BFS (Bredth First Search) to do shortest distances
*/
#define WALL '#'
#define PATH '.'

struct point
{
	int x;
	int y;
};

struct queueNode
{
	point pt;
	int dist;
};

bool isValid(int row, int col, int width, int height)
{
	bool result = ((row >= 0) && (row < width) &&
			(col >= 0) && (col < height));

	//cout<<"helper fundtion:"<<row<<","<<col<<" "<<width<<" "<<height<<"  "<<result<<endl;

	return result;
}

int bfs(char *mat, point src, point dest, int width, int height, char enemy)
{
	if (mat[(src.y * width) + src.x] == WALL || !mat[(dest.y * width) + dest.x] == WALL)
		return -1;

	bool visited[width * height];
	memset(visited, false, sizeof(visited));

	// mark src as visited
	visited[(src.y * width) + src.x] = true;

	queue<queueNode> q;
	queueNode s = {src, 0};
	q.push(s);

	int rowNum[] = {-1, 0, 0, 1};
	int colNum[] = {0, -1, 1, 0};

	while (!q.empty())
	{

		queueNode curr = q.front();
		point pt = curr.pt;
		//cout<<"     looking @ "<<pt.x<<","<<pt.y<<" d:"<<curr.dist<<endl;

		if (pt.x == dest.x && pt.y == dest.y)
			return curr.dist;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int row = pt.x + rowNum[i];
			int col = pt.y + colNum[i];
		
			if ((isValid(row, col, width, height)) && (!visited[(col * width) + row]) && ((mat[(col * width) + row] == PATH) || (mat[(col * width) + row] == enemy)))
			{
				//cout<<"pushing "<<row<<","<<col<<endl;
				visited[(col * width) + row] = true;
				queueNode adjcell = { {row, col}, curr.dist + 1 };
				q.push(adjcell);
			}
		}
	}
	return -1;
}


/*
	unit class + types
*/

enum unit_type_t { ELF, GOBLIN };
typedef struct xy_s
{
	int x;
	int y;
	bool operator!=(const xy_s &i)
	{
		return ((x != i.x) || (y != i.y));
	}
	bool operator==(const xy_s &i)
	{
		return ((x == i.x) && (y == i.y));
	}
} xy_s;

//bool operator!=(const xy_s &lhs, const xy_s &rhs) { return ((lhs.x != rhs.x) || (lhs.y != lhs.y)); }

typedef struct hw
{
	int h;
	int w;
} hw_s;


typedef struct winner_details
{
	int rounds;
	int hp_left;
	int lost_winning_units;
	unit_type_t winner_type;
} winner_details;


class unit {

public:

	int id;
	int ap;
	int hp;
	bool alive;
	
	char *grid;
	vector<unit*> *all_units;
	hw_s grid_hw;

	char enemy_char;
	unit_type_t ut;
	xy_s xy;

	vector<xy_s> possible_targets;
	vector<xy_s> possible_adj_targets;
	vector<xy_s> possible_moves;
	vector<xy_s> adj_to_unit;

	bool in_melee;
	//vector<unit*> enemies_in_melee; //vector of pointers of unit type of enemies- keep this local instead
	unit* ptr_per_id(int);

	unit(int id_c, xy_s xy_c, int ap_c, int hp_c, unit_type_t ut_c, char e_t, char *grid_c, hw_s u, vector<unit*> *all_units_c) : 
		id(id_c), xy(xy_c), ap(ap_c), hp(hp_c), ut(ut_c), enemy_char(e_t), grid_hw(u), alive(true) { unit::all_units = all_units_c; unit::grid = grid_c; };

	vector<xy_s> find_possible_targets(void);
	vector<xy_s> find_possible_adj_targets(void);
	xy_s find_next_move(void);
	void are_we_in_melee(void);

	bool process_turn(void);
	void move(xy_s);
	void attack(unit*);
	bool is_it_char(char, int, int, hw_s);
	vector<xy_s> check_adj(xy_s, char);
	int find_id_by_xy(xy_s);

};

vector<xy_s> unit::find_possible_targets(void)
{
	unit_type_t enemy_type;
	if (unit::ut == ELF)
		enemy_type = GOBLIN;
	else if (unit::ut == GOBLIN)
		enemy_type = ELF;

	vector<xy_s> enemy_targets;
	for (const auto &i: *unit::all_units)
		if ((i->ut == enemy_type) && (i->alive == true))
			enemy_targets.push_back(i->xy);

	return enemy_targets;
}

vector<xy_s> unit::find_possible_adj_targets(void)
{
	vector<xy_s> tmp_in_range;
	vector<xy_s> in_range;
	xy_s tmp;
	for (const auto &i: unit::possible_targets)
	{
		//cout<<"possible target:"<<i.x<<","<<i.y<<endl;
		tmp_in_range = unit::check_adj(i, '.');
		if (tmp_in_range.size() > 0)
			for (const auto &u: tmp_in_range)
				in_range.push_back(u);
	}
	return in_range;
}

vector<xy_s> unit::check_adj(xy_s xy, char what)
{
	vector<xy_s> in_range;
	xy_s tmp = xy;

	int rowNum[] = {-1, 0, 0, 1};
	int colNum[] = {0, -1, 1, 0};

	for (int x = 0; x < 4; x++)
	{
		if (unit::is_it_char(what, xy.x + rowNum[x], xy.y + colNum[x], unit::grid_hw) == true)
		{
			tmp.x = xy.x + rowNum[x];
			tmp.y = xy.y + colNum[x];
			in_range.push_back(tmp);
		}
	}

	return in_range;
}

bool unit::is_it_char(char what, int x, int y, hw_s hw)
{
	if (unit::grid[(y * hw.w) + x] == what)
		return true;
	else
		return false;
}

xy_s unit::find_next_move(void)
{
	// run BFA algo from current position to each enemy
	int closest_enemy_id;
	vector<xy_s> enemies;

	point source, dest;
	source.x = unit::xy.x;
	source.y = unit::xy.y;
	bool first = true;

	for (const auto &i: unit::possible_targets)
	{
		dest.x = i.x;
		dest.y = i.y;

		// find closest enemy
		int tmp = bfs(unit::grid, source, dest, unit::grid_hw.w, unit::grid_hw.h, unit::enemy_char);
		//cout<<"closest_enemy     "<<source.x<<","<<source.y<<"  trying "<<dest.x<<","<<dest.y<<"  for enemy "<<unit::enemy_char<<" BFS:"<<tmp<<endl;
		if (first == true)
		{
			first = false;
			enemies.push_back(i);
			closest_enemy_id = tmp;

		} else if (((tmp < closest_enemy_id) || (closest_enemy_id == -1)) && (tmp >= 0))
		{
			closest_enemy_id = tmp;
			enemies.clear();
			enemies.push_back(i);
		
		} else if (tmp == closest_enemy_id)
		{
			enemies.push_back(i);
		
		}
	}


	// if any ties, break the tie
	xy_s next_enemy;
	first = true;
	if (enemies.size() > 1)
	{
		int lowest_grid_value;
		for (const auto &i: enemies)
		{
			int this_grid_value = ((i.y * unit::grid_hw.w) + i.x);

			if (first == true)
			{
				first = false;
				lowest_grid_value = this_grid_value;
				next_enemy = i;

			} else if (this_grid_value < lowest_grid_value)
			{
				lowest_grid_value = this_grid_value;
				next_enemy = i;
			}
		}

	} else if (enemies.size() == 1) {
		
		next_enemy = enemies.at(0);
		//cout<<"next enemy is:"<<next_enemy.x<<","<<next_enemy.y<<endl;
	}

	// next_enemy is xy co-ord of next enemy, now work out which move to make
	// grab possible moves from current location
	vector<xy_s> adj_moves = unit::check_adj(unit::xy, '.');
	vector<xy_s> lowest_next_move;
	int value_of_lowest_move = 0;
	first = true;
	//cout<<"adj moves:"<<adj_moves.size()<<endl;
	// run BFS over each of these
	for (const auto &i: adj_moves)
	{
		
		// change types over- xy_s to be same as point
		point source, dest;
		source.x = i.x;
		source.y = i.y;
		dest.x = next_enemy.x;
		dest.y = next_enemy.y;

		// find closest enemy
		int tmp = bfs(unit::grid, source, dest, unit::grid_hw.w, unit::grid_hw.h, unit::enemy_char);

		//cout<<"       trying "<<i.x<<","<<i.y<<"  for enemy @ "<<dest.x<<","<<dest.y<<" BFS:"<<tmp<<"   "<<value_of_lowest_move<<endl;

		if (first == true)
		{
			//cout<<"first"<<endl;
			first = false;
			lowest_next_move.push_back(i);
			value_of_lowest_move = tmp;

		} else if (((tmp < value_of_lowest_move) || (value_of_lowest_move == -1)) && (tmp >= 0))
		{
			value_of_lowest_move = tmp;
			lowest_next_move.clear();
			//cout<<"clearing....."<<lowest_next_move.size()<<endl;
			lowest_next_move.push_back(i);
		
		} else if (tmp == value_of_lowest_move)
		{
			//cout<<" three.."<<endl;
			lowest_next_move.push_back(i);
		}
	}

	// break out if no path to enemy
	if ((value_of_lowest_move == -1) || (adj_moves.size() == 0))
		return unit::xy;

	//cout<<"size of:"<<lowest_next_move.size()<<endl;

	// tie break if need be
	xy_s next_move;
	first = true;
	if (lowest_next_move.size() > 1)
	{
		int lowest_grid_value;
		for (const auto &i: lowest_next_move)
		{
			int this_grid_value = ((i.y * unit::grid_hw.w) + i.x);
			//cout<<"TIE BREAK: "<<i.x<<","<<i.y<<":"<<this_grid_value<<endl;

			if (first == true)
			{
				first = false;
				lowest_grid_value = this_grid_value;
				next_move = i;

			} else if (this_grid_value < lowest_grid_value)
			{
				lowest_grid_value = this_grid_value;
				next_move = i;
			}
		}
	} else {

		next_move = lowest_next_move.at(0);
	}

	//cout<<"move to:"<<next_move.x<<","<<next_move.y<<endl;

	return next_move;
}

int unit::find_id_by_xy(xy_s xy)
{
	for (const auto &i: *unit::all_units)
		if ((i->xy.x == xy.x) && (i->xy.y == xy.y))
			return i->id;
	return -1;
}

unit* unit::ptr_per_id(int id)
{
	unit *return_value;
	for (const auto &i: *unit::all_units)
		if (i->id == id)
		{
			return_value = i;
			return return_value;
		}
	return NULL;
}

void unit::are_we_in_melee(void)
{
	if (unit::ut == ELF)
		unit::adj_to_unit = unit::check_adj(unit::xy, 'G');
	else
		unit::adj_to_unit = unit::check_adj(unit::xy, 'E');

	// are we in melee?
	if (adj_to_unit.size() == 0)
		unit::in_melee = false;
	else
		unit::in_melee = true;
}

bool unit::process_turn(void)
{

	if (unit::alive == false)
		return false;

	//cout<<endl<<"Turns for:"<<unit::id<<" "<<unit::xy.x<<","<<unit::xy.y<<" "<<unit::ut<<endl;

	// Each unit begins its turn by identifying all possible targets (enemy units). 
	unit::possible_targets = unit::find_possible_targets();

	// If no targets remain, combat ends.
	if (unit::possible_targets.size() == 0)
		return true;

	// Then, the unit identifies all of the open squares (.) that are in range of each target;
	unit::possible_adj_targets = unit::find_possible_adj_targets();

	// If the unit is not already in range of a target, and there are no open squares which are in range of a target, the unit ends its turn.

	unit::are_we_in_melee();	

	// If the unit is already in range of a target, it does not move, but continues its turn with an attack.
	if (unit::in_melee == false)
	{
		// Otherwise, since it is not in range of a target, it moves.
		// find move
		xy_s next_move = unit::find_next_move();
		//cout<<"next move found:"<<next_move.x<<","<<next_move.y<<endl;

		// if next_move == unit::xy, then no path was found, no action
		if (next_move != unit::xy)
		{
			//cout<<"attempting to move to "<<next_move.x<<","<<next_move.y<<endl;

			// implement it
			unit::move(next_move);
		}
	}

	unit::are_we_in_melee();	

	if (unit::in_melee == true)
	{
		// ptr to every enemy in range
		vector<unit*> enemies_in_melee;
		for (const auto &i: adj_to_unit)
		{
			//if adjacent unit isn't in our known list, add it
			int tmp_id = unit::find_id_by_xy(i);

			// send id to unit::ptr_per_id, adds pointer to unit::enemies_in_melee
			enemies_in_melee.push_back(unit::ptr_per_id(tmp_id));
		}

		// find one with lowest id
		int lowest_hp;
		unit *lowest_hp_unit;
		vector<unit*> vec_enemies = {};
		bool first = true;
		for (const auto &i: enemies_in_melee)
		{
			if (first == true)
			{
				first = false;
				lowest_hp = i->hp;
				vec_enemies.push_back(i);
			
			} else if (i->hp < lowest_hp)
			{
				lowest_hp = i->hp;
				vec_enemies.clear();
				vec_enemies.push_back(i);
			
			} else if (i->hp == lowest_hp)
			{
				vec_enemies.push_back(i);
			}
		}

		// if tie, use tie break
		unit* target;
		if (vec_enemies.size() > 1)
		{
			bool first = true;
			int lowest_grid_value = 0;
			for (const auto &i: vec_enemies)
			{
				int this_grid_value = ((i->xy.y * unit::grid_hw.w) + i->xy.x);

				if (first == true)
				{
					first = false;
					lowest_grid_value = this_grid_value;
					target = i;
				
				} else if (this_grid_value < lowest_grid_value)
				{
					lowest_grid_value = this_grid_value;
					target = i;
				}
			}
		} else {
			target = vec_enemies.at(0);
		}

		// for some reason had to do this-
		if (target->alive == true)
			unit::attack(target);

	} 
	// turn over

	
	//cout<<endl;

	return false;
}

void unit::move(xy_s xy)
{
	// set existing xy to '.'
	unit::grid[(unit::xy.y * unit::grid_hw.w) + unit::xy.x] = '.';

	char unit;
	if (unit::ut == GOBLIN)
		unit = 'G';
	else
		unit = 'E';
	unit::grid[(xy.y * unit::grid_hw.w) + xy.x] = unit;

	// move current unit position to xy
	unit::xy = xy;
}

void unit::attack(unit *target)
{
	// do attack
	target->hp -= unit::ap;

	// is enemy dead?
	if (target->hp <= 0)
	{
		target->alive = false;

		unit::grid[(target->xy.y * unit::grid_hw.w) + target->xy.x] = '.';

		target->xy.x = 0;
		target->xy.y = 0;
	}
}

void print_units(vector<unit*> units)
{
	for (const auto &i: units)
	{
		cout<<"id:"<<i->id<<" "<<"xy:"<<i->xy.x<<","<<i->xy.y<<endl;
		if (i->ut == GOBLIN) cout<<"Goblin"<<endl;
		if (i->ut == ELF) cout<<"Elf"<<endl;
		cout<<"hp:"<<i->hp<<" ap:"<<i->ap<<endl;
		cout<<endl;
	}
}

void print_unit_status(vector<unit*> *units)
{
	char t;
	for (const auto &i: *units)
	{
		if (i->ut == GOBLIN)
			t = 'G';
		else
			t = 'E';
		cout<<"Unit:"<<i->id<<" "<<t<<" "<<"HP:"<<i->hp<<" status:"<<i->alive<<endl;
	}
	cout<<endl;
}

winner_details is_combat_over(vector<unit*> *units)
{
	vector<unit*> alive_goblins = {};
	vector<unit*> alive_elves = {};
	for (const auto &i: *units)
		if (i->alive == true)
			if (i->ut == ELF)
				alive_elves.push_back(i);
			else
				alive_goblins.push_back(i);

	winner_details result;
	result.hp_left = 0;
	result.rounds = 0;
	result.lost_winning_units = 0;

	if (alive_goblins.size() > 0 && alive_elves.size() == 0)
	{
		//cout<<"goblins win";
		for (const auto &i: *units)
			if ((i->alive == false) && (i->ut == GOBLIN))	
				result.lost_winning_units++;

		result.winner_type = GOBLIN;
		for (const auto &i: alive_goblins)
			result.hp_left += i->hp;

	} else if (alive_elves.size() > 0 && alive_goblins.size() == 0)
	{
		//cout<<"elves win";
		for (const auto &i: *units)
			if ((i->alive == false) && (i->ut == ELF))	
				result.lost_winning_units++;

		result.winner_type = ELF;
		for (const auto &i: alive_elves)
			result.hp_left += i->hp;
	}

	return result;
}

void print_grid(char *grid, hw_s hw)
{
	for (int y = 0; y < hw.h; y++)
	{
		for (int x = 0; x < hw.w; x++)
			cout<<grid[(hw.w * y) + x];
		cout<<endl;
	}
}

vector<unit*> find_order_of_turns(vector<unit*> *units, hw_s hw)
{
	vector<unit*> order_of_turns;
	for (int y = 0; y < hw.h; y++)
		for (int x = 0; x < hw.w; x++)
		{
			xy_s tmp;
			tmp.x = x;
			tmp.y = y;
			for (const auto &i: *units)
				if ((tmp.x == i->xy.x) && (tmp.y == i->xy.y) && (i->alive == true))
				{
					unit *tmp_c = i;
					order_of_turns.push_back(tmp_c);
				}
		}
	return order_of_turns;
}



winner_details combat_sim(int power_increase)
{
	hw_s hw;
	char *grid = grab_input("input", hw.h, hw.w);
	//print_grid(grid, hw);

	// parse the grid, generate units into vector of pointers
	int id = 0;
	vector<unit*> *units = new vector<unit*>;
	for (int y = 0; y < hw.h; y++)
		for (int x = 0; x < hw.w; x++)
		{
			char current_point = grid[(hw.w * y) + x];
			if (current_point == 'G')
			{
				xy_s p;
				p.x = x;
				p.y = y;
				unit *new_unit = new unit(id, p, 3, 200, GOBLIN, 'E', grid, hw, units);
				units->push_back(new_unit);
				id++;

			} else if (current_point == 'E')
			{
				xy_s p;
				p.x = x;
				p.y = y;
				unit *new_unit = new unit(id, p, power_increase, 200, ELF, 'G', grid, hw, units);
				units->push_back(new_unit);
				id++;

			}
			
		}

	// verify order of turns
	vector<unit*> order_of_turns = find_order_of_turns(units, hw);
		
	int total_turns = 0;
	int score = 0;
	winner_details result;
	result.hp_left = 0;
	while (1)
	{
		// order of turns for units
		order_of_turns = find_order_of_turns(units, hw);
		
		bool combat_ends;
		for (const auto &i: order_of_turns)
		{
			combat_ends = i->process_turn();

			if (combat_ends == true)
				break;
		}

		if (combat_ends == true)
			break;
		
		total_turns++;

		result = is_combat_over(units);
		if (result.hp_left > 0)
			break;
	}


	result = is_combat_over(units);
	result.rounds = total_turns;

	delete[] grid;

	// clean up
	for (auto &i: *units)
		delete i;

	delete units;

	return result;
}

int main()
{
	winner_details part_one;
	part_one = combat_sim(3);
	cout<<part_one.rounds<<" * "<<part_one.hp_left<<" = "<<(part_one.rounds * part_one.hp_left)<<endl;

	// part two
	winner_details part_two;
	int ap_increase = 4;
	while (1)
	{
		part_two = combat_sim(ap_increase);
		if ((part_two.winner_type == ELF) && (part_two.lost_winning_units == 0))
			break;

		ap_increase++;
	}
	cout<<"power increase:"<<ap_increase<<" "<<part_two.rounds<<" * "<<part_two.hp_left<<" = "<<(part_two.rounds * part_two.hp_left)<<endl;

	return 0;
}
