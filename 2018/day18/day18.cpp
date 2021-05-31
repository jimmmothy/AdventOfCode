#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

typedef struct change
{
	int x;
	int y;
	char new_char;
} change;

void print_grid(char *grid, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			cout<<grid[(y * width) + x];
		cout<<endl;
	}
}

bool valid_xy(int x, int y, int width, int height)
{
	if (y < 0)
		return false;
	else if (y >= height)
		return false;
	
	if (x < 0)
		return false;
	else if (x >= width)
		return false;

	return true;
}

change check_xy(char *grid, int x, int y, int width, int height)
{
	int y_change[9] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int x_change[9] = {-1, 0, 1, 1, 1, 0, -1, -1};
	
	int open_ground = 0;
	int trees = 0;
	int lumberyard = 0;

	for (int z = 0; z < 8; z++)
	{
		if (valid_xy((x + x_change[z]), (y + y_change[z]), width, height))
		{
			char x_char = grid[(width * (y + y_change[z])) + (x + x_change[z])];
			if (x_char == '.')
				open_ground++;
			else if (x_char == '|')
				trees++;
			else if (x_char == '#')
				lumberyard++;
		}
	}
	char current = grid[(width * y) + x];
	char new_char = '0';

	if (current == '.')
	{
		if (trees >= 3)
			new_char = '|';

	} else if(current == '|')
	{
		if (lumberyard >= 3)
			new_char = '#';

	} else if (current == '#')
	{
		if (lumberyard >= 1 && trees >= 1)
			new_char = '#';
		else
			new_char = '.';
	}
	
	change new_change;
	new_change.x = x;
	new_change.y = y;
	new_change.new_char = new_char;
	
	return new_change;
}

void do_minute(char *grid, int width, int height)
{
	// find changes
	vector<change> changes_to_do;
	for (int y = 0; y < height; y++)
		for (int x = 0; x < height; x++)
		{
			change this_xy = check_xy(grid, x, y, width, height);
			if (this_xy.new_char != '0')
			{
				//cout<<x<<","<<y<<" to become:"<<this_xy.new_char<<endl;
				changes_to_do.push_back(this_xy);
			}

		}
	
	// implement changes
	for (const auto& i: changes_to_do)
		grid[(width * i.y) + i.x] = i.new_char;
}

int count_char(char *grid, char what, int width, int height)
{
	int count = 0;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (grid[(width * y) + x] == what)
				count++;
	return count;
}

int main()
{
	// open file
	ifstream file;
	file.open("input");
	if (!file)
	{
		cerr<<"Error!"<<endl;
		return 1;
	}
	string line;
	vector<string> all_lines;
	while (getline(file, line))
	{
		all_lines.push_back(line);
	}

	int width = all_lines.at(0).length();
	int height = all_lines.size();

	// generate grid
	char *grid = new char[width * height];
	int counter = 0;
	for (const auto &i: all_lines)
		for (const auto &u: i)
		{
			grid[counter] = u;
			counter++;
		}

	int count = 0;
	int previous_seq = 0;
	vector<int> numbers;
	vector<pair<int, int>> seq_count;
	while (1)
	{
		count++;
		do_minute(grid, width, height);
		
		int total_tree = (count_char(grid, '|', width, height));
		int total_lumber = (count_char(grid, '#', width, height));
		int total_count = total_tree * total_lumber;

		bool found = false;
		for (const auto &i: numbers)
		{
			if (i == total_count)
				found = true;
		}
		if (found == false)
		{
			numbers.push_back(total_count);
		
		} else if (found == true)
		{
			if (seq_count.size() > 0)
				// if our sequence counter isn't sequential, or total count is the same for two iterations, clear it
				if ((seq_count.back().first != (count - 1)) || (seq_count.back().second == total_count))
					seq_count.clear();

			seq_count.push_back(make_pair(count, total_count));
		}

		// look for sequential numbers of count for found total number
		// when every one for say 20+ shows up then we have a repeating sequence
		// find the start and end from when the first element shows up again

		found = false;
		if (seq_count.size() > 0)
		{
			pair<int, int> start = seq_count.at(0);
			for (const auto &i: seq_count)
				if (i != start)
					// this should only occur when the first element is repeated after >1 minutes
					if (start.second == i.second)
						found = true;
		}
		if (found == true)
		{
			seq_count.pop_back();
			break;
		}

	}

	// seq_count now has our array of offsets of repeating numbers
	// minus the count from target, and mod by length of vector for position of offset that's the answer
	int offset = (1000000000 - seq_count.at(0).first) % seq_count.size();
	cout<<seq_count.at(offset).second<<endl;

	// clean up
	delete[] grid;
	return 0;
}
