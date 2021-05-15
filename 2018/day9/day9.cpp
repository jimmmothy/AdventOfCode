#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

typedef struct marble
{
	int id;
	marble *previous;
	marble *next;
} marble;

typedef struct player
{
	int id;
	long double score;
} player;

enum direction_t {LEFT, RIGHT};

class day
{
	double m_count;
	double m_max;
	int p_count;
	int c_player;
public:
	day(int x, int y) : p_count(x), m_max(y), m_count(1), c_player(1) {};
	long double part1();
	vector<player>* init_players(int);
	void clean_players(vector<player>*);
	void clean_marbles(marble*);
	marble* next_move(marble*, vector<player>&);
	marble* find_move(direction_t, int, marble*);
	marble* remove_marble(marble*, direction_t);
	void inc_score(int, int, vector<player>&);
	void inc_player(void);
};

/*
	use init_player to establish players- accepts number
	of players, returns pointer struct array of players

	set player and marble count as private class vars
	use a function next_move to process the next move,
	accept pointer to current head as argument, return 
	pointer to new head

	each iteration of next_move will create a new marble,
	and find where it needs to slot in the existing chain
		where n%23 !=0, move two to the right
		where n%23 == 0, new marble that would have been placed is deleted, and added to score
		and marble 7 to the left is also deleted and added to score

	find_move accepts a direction, the number of moves, and start point, returns a pointer
	to the marble found at that location

	remove_marble accepts a pointer of marble that needs to be deleted, as well as the direction
	of the pointer to return. i.e. 1 2 3 4 5, say we remove 3 and have RIGHT as the direction, 
	we delete marble 3, change 2's next to 4, and 4s previous to 2, and return a pointer to marble 4
*/


vector<player> *day::init_players(int r_input)
{
	vector<player> *ret_a = new vector<player>;
	for (int x = 0; x < r_input; x++)
	{
		player c_player;
		c_player.id = x;
		c_player.score = 0;
		ret_a->push_back(c_player);
	}
	return ret_a;
}

void day::clean_players(vector<player> *pvec)
{
	delete pvec;
}

// Can't seem to do this section right, so potato-code
void day::clean_marbles(marble *r_input)
{
	marble *last = r_input->previous;
	marble *current = r_input;
	marble *to_delete;

	while (current != last)
	{
		to_delete = current;
		current = current->next;
		delete to_delete;
	}

	delete last;
}


void day::inc_score(int score, int player_id, vector<player> &players)
{
	for (auto &i: players)
		if (i.id == player_id)
			i.score += score;
}

void day::inc_player(void)
{
	if (day::c_player == day::p_count)
		day::c_player = 1;
	else
		day::c_player++;
}


marble* day::next_move(marble* r_input, vector<player> &players)
{
	double twentythree = 23;

	if (day::m_count == 1)
	{
		marble *new_marble = new marble;
		new_marble->id = day::m_count;
		day::m_count++;
		r_input->next = new_marble;
		r_input->previous = new_marble;
		new_marble->next = r_input;
		new_marble->previous = r_input;

		day::inc_player();
		return new_marble;
	
	} else if (fmod(day::m_count, twentythree) != 0)
	{
		marble *new_marble = new marble;
		new_marble->id = day::m_count;
		day::m_count++;

		// slot new marble in, two to the right
		marble *tmp_r_marble = day::find_move(RIGHT, 2, r_input);
		marble *tmp_l_marble = tmp_r_marble->previous;
		tmp_l_marble->next = new_marble;
		new_marble->previous = tmp_l_marble;
		new_marble->next = tmp_r_marble;
		tmp_r_marble->previous = new_marble;

		day::inc_player();
		return new_marble;

	} else {

		// increment player score by current marble
		day::inc_score(day::m_count, day::c_player, players);
		day::m_count++;

		marble *tmp_marble = day::find_move(LEFT, 7, r_input);
		day::inc_score(tmp_marble->id, day::c_player, players);
		marble *new_marble = day::remove_marble(tmp_marble, RIGHT);

		day::inc_player();
		return new_marble;
	}
}

marble* day::remove_marble(marble *r_input, direction_t direction)
{
	marble *tmp_prev = r_input->previous;
	marble *tmp_next = r_input->next;

	tmp_prev->next = tmp_next;
	tmp_next->previous = tmp_prev;

	marble *ret_a;
	if (direction == LEFT)
		ret_a = tmp_prev;
	else
		ret_a = tmp_next;

	delete r_input;

	return ret_a;
}

marble* day::find_move(direction_t direction, int distance, marble* r_input)
{
	marble *tmp = r_input;

	if (direction == LEFT)
		for (int x = 0; x < distance; x++)
			tmp = tmp->previous;
	else if (direction == RIGHT)
		for (int x = 0; x < distance; x++)
			tmp = tmp->next;

	return tmp;
}

long double day::part1()
{
	vector<player> *players = day::init_players(day::p_count);
	
	// keep reference to first marble
	marble *first_marble = new marble;
	first_marble->id = 0;

	marble *new_head = first_marble;
	for (int x = 0; x < day::m_max; x++)
	{
		new_head = day::next_move(new_head, *players);
	}

	double answer = 0;
	for (const auto &i: *players)
		if (i.score > answer)
			answer = i.score;

	day::clean_marbles(first_marble);
	day::clean_players(players);
	
	return answer;
}


int main()
{
	day nine(428, 72061);
	cout<<nine.part1()<<endl;

	day ninep2(428, 7206100);
	cout<<fixed<<ninep2.part1()<<endl;

	return 0;
}