#include <string>
#include <vector>
#include <iostream>

using namespace std;

double sequence_found(vector<int> scoreboard, string input, int index)
{
	// Turn scoreboard into string
	/*string tmp_str;
	for (int x = index; x < scoreboard.size() - 1; x++)
		tmp_str += scoreboard.at(x);
	cout<<tmp_str.length()<<endl;
	cout<<tmp_str<<endl;*/

	string tmp_str2;
	for (const auto &i: scoreboard)
		tmp_str2 += to_string(i);

	string tmp_str;
	for (int x = index; x < tmp_str2.size(); x++)
		tmp_str += tmp_str2.at(x);
	
	// Search string for sequence
	string buff;
	double answer = 0;
	for (int x = 0; x <= (tmp_str.length() - input.length()); x++)
	{
		buff = "";
		for (int y = 0; y < input.length(); y++)
			buff += tmp_str.at(x + y);

		//cout<<buff<<" ";
		if (buff == input)
		{
			answer = x;
			break;
		}
	}

	return answer;
}


int find_recipes(string input)
{
	vector<int> scoreboard = { 3, 7 };
	int elf_one = 0;
	int elf_two = 1;

	double resp;
	int input_length = input.length();

	int limit;
	int next_lot = 10;

	int index = 0;

	while (1)
	{
		limit = scoreboard.size();
		if (elf_one >= limit)
			elf_one %= limit;
		if (elf_two >= limit)
			elf_two %= limit;

		int new_score = scoreboard.at(elf_one) + scoreboard.at(elf_two);

		string s_new_score = to_string(new_score);
		for (const auto &i: s_new_score)
		{
			int x = static_cast<int>(i) - 48;
			scoreboard.push_back(x);
		}

		elf_one += 1 + scoreboard.at(elf_one);
		elf_two += 1 + scoreboard.at(elf_two);

		// save time by only searching in larger chunks
		if (limit - index >= (input_length * 1000000))
		{
			//cout<<"limit:"<<limit<<" index:"<<index<<endl;
			resp = sequence_found(scoreboard, input, index);
			if (resp > 0)
				break;
			else
				index = limit-5;
		}
	}

	return resp+index;
}

int main()
{
	vector<int> scoreboard = { 3, 7 };
	int elf_one = 0;
	int elf_two = 1;

	int limit;
	int skill_improve = 846601;
	int next_lot = 10;
	int looking_for = skill_improve + next_lot;

	while (1)
	{
		limit = scoreboard.size();
		if (elf_one >= limit)
			elf_one %= limit;
		if (elf_two >= limit)
			elf_two %= limit;

		if (limit >= looking_for)
			break;

		int new_score = scoreboard.at(elf_one) + scoreboard.at(elf_two);

		string s_new_score = to_string(new_score);
		for (const auto &i: s_new_score)
		{
			int x = static_cast<int>(i) - 48;
			scoreboard.push_back(x);
		}

		elf_one += 1 + scoreboard.at(elf_one);
		elf_two += 1 + scoreboard.at(elf_two);
	}

	string tmp_str;
	int counter = 0;
	for (const auto &i: scoreboard)
	{
		if ((counter >= skill_improve) && (counter < looking_for))
			tmp_str += to_string(i);
		counter++;
	}
	cout<<tmp_str<<endl;

	// part two
	//cout<<find_recipes("51589")<<endl;
	//cout<<find_recipes("01245")<<endl;
	//cout<<find_recipes("92510")<<endl;
	//cout<<find_recipes("59414")<<endl;
	cout<<find_recipes("846601")<<endl;


	return 0;
}
