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
	vector<int> vecint(void);
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

vector<int> aoc_input::vecint(void) 
{
	vector<int> tmp_vc;
	string tmp_s;

	if (!aoc_input::open_file())
		return tmp_vc;

	string str;
	while (getline(aoc_input::aoc_file, str)) {
		if (str.size() > 0)
			tmp_s += str;
	}

	aoc_input::aoc_file.close();

	string buff;
	for (const auto &i: tmp_s)
	{
		if (i != ' ')
			buff += i;
		else if (i == ' ')
		{
			tmp_vc.push_back(stoi(buff));
			buff = "";
		}
	}
	tmp_vc.push_back(stoi(buff));

	return tmp_vc;
}

/*********************************************************/
/*********************************************************/
/*********************************************************/
/*********************************************************/

typedef struct tree 
{
	int id;
	int cnode_count;
	int mdata_count;
	int mdata_value;
	// where on tree_data it starts and ends
	int data_start;
	int data_end;
	vector<int> mdata_entries;
	vector<tree*> children;
} tree;

class day
{
private:
	vector<int> tree_data;
	int global_count;

public:
	day();
	int part1();
	int part2();
	pair<int, int> find_metadata_p1(int, int);
	tree* find_metadata_p2(int, int);
	void clean_part2(tree*);
};

day::day()
{
	aoc_input data_class("input");
	day::tree_data = data_class.vecint();
	day::global_count = 0;
}

/* 
	have a function, pair<int, int> find_metadata(int sp, int count)
	run this on first entry as (pc=0, count=1), count will be 1
	because we're only looking at the first entry

	this then reads sp (0), see's there's two children, and three 
	metadata entries (pc+1), then calls find_metadata(sp=2, count=2)
	each find_metadata entry will return the total meta_data within it

	find_metadata() will search for child nodes, call itself for each child node,
	and return a pair<int=new pc, int=metadata total> for total contained metadata and the new pc
	which it uses to calcute the existing node's meta data

2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2
A----------------------------------
    B----------- C-----------
                     D-----

	i.e.
	find_metadata(0, 1)
		find_metadata(2, 2)
			find_metadata(9, 1)
			returns 12,99
		returns 13, 2+(99)
	returns 16/EOF, 1+1+2+(99+2)
*/

pair<int, int> day::find_metadata_p1(int pc, int count)
{
	 int current_pc = pc;
	 pair<int, int> ret_b;
	 int mdata_value = 0;
	 int mdata_count;
	 int cnode_count;

	 // need to loop for count times
	 for (int y = 0; y < count; y++)
	 {
		int cnode_count = day::tree_data.at(current_pc);
		int mdata_count = day::tree_data.at(current_pc + 1);

		// child nodes found, start recursion
		if (cnode_count > 0)
		{
			pair<int, int> ret_a;
		 	ret_a = day::find_metadata_p1(current_pc + 2, cnode_count);

		 	mdata_value += ret_a.second;
		 	current_pc = ret_a.first;
		} else {
		 	// manually inc pc by 2, child node above returns absolute pc instead
		 	current_pc += 2;
		}

		 // now add meta data values for this instance
		for (int x = current_pc; x < current_pc + mdata_count; x++)
		 	mdata_value += day::tree_data.at(x);

		current_pc += mdata_count;
	}

	ret_b = make_pair(current_pc, mdata_value);
	return ret_b;
}

int day::part1()
{
	pair<int, int> answer;
	answer = day::find_metadata_p1(0, 1);

	return answer.second;
}


tree* day::find_metadata_p2(int pc, int count)
{
	int current_pc = pc;

	tree *ret_v = new tree;
	ret_v->id = day::global_count;
	day::global_count++;
	ret_v->mdata_entries = {};
	ret_v->mdata_value = 0;
	
	ret_v->data_start = current_pc;
	ret_v->cnode_count = day::tree_data.at(current_pc);
	ret_v->mdata_count = day::tree_data.at(current_pc + 1);
	
	current_pc += 2;

	// child nodes found, start recursion
	if (ret_v->cnode_count > 0)
	{
		// allocate new child
		for (int a = 0; a < ret_v->cnode_count; a++)
		{
			tree *ret_a = day::find_metadata_p2(current_pc, ret_v->cnode_count);
		 	current_pc = ret_a->data_end;
		 	ret_v->children.push_back(ret_a);
		}
	}

	// fill out meta data entries
	for (int x = current_pc; x < current_pc + ret_v->mdata_count; x++)
		ret_v->mdata_entries.push_back(day::tree_data.at(x));

	// now add meta data values for this instance
	if (ret_v->cnode_count > 0)
	{
		for (const auto &i: ret_v->mdata_entries)
		{
			if (i <= ret_v->cnode_count)
			{
				tree * tmp_t = ret_v->children.at(i-1);
				ret_v->mdata_value += tmp_t->mdata_value;
			}
		}
	} else	{
		// sum of entries where no child nodes exist
	 	for (const auto &i: ret_v->mdata_entries)
	 		ret_v->mdata_value += i;
	}

	current_pc += ret_v->mdata_count;
	ret_v->data_end = current_pc;

	return ret_v;
}

void day::clean_part2(tree * r_input)
{
	if (r_input->children.size() > 0)
	{
		for (auto &i: r_input->children)
			day::clean_part2(i);
	}
	delete r_input;
}

int day::part2()
{
	tree *tree_ptr;
	tree_ptr = day::find_metadata_p2(0, 1);
	int answer = tree_ptr->mdata_value;
	day::clean_part2(tree_ptr);
	return answer;
}

int main()
{
	day eight;
	cout<<eight.part1()<<endl;
	cout<<eight.part2()<<endl;

	return 0;
}