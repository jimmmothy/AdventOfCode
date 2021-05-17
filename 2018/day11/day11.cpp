#include <iostream>
#include <cmath>
#include <utility>
#include <thread>
#include <vector>

using namespace std;

int calculate_pl(int x, int y, int grid_serial)
{
	int rack_id = x + 10;
	int power_level = rack_id * y;
	power_level += grid_serial;
	power_level = power_level * rack_id;
	int hundred = ((power_level - (power_level % 100)) % 1000) / 100;

	return hundred - 5;
}

pair<int, int> part1(int grid_serial)
{
	int width = 300;
	int height = 300;
	int square = 3;
	int highest_power = 0;
	int current_power;
	pair<int, int> current_answer;

	for (int x = 1; x < (width + 1 - square); x++)
		for (int y = 1; y < (height + 1 - square); y++)
		{
			// loop through offsets
			current_power = 0;
			for (int q = 0; q < square; q++)
				for (int w = 0; w < square; w++)
					current_power += calculate_pl(x + q, y + w, grid_serial);

			if (current_power > highest_power)
			{
				highest_power = current_power;
				current_answer = make_pair(x, y);
			}
		}

	return current_answer;
}

typedef struct p2answer
{
	int x, y, ss;
} p2answer;

p2answer part2(int grid_serial)
{
	int width = 300;
	int height = 300;
	int highest_power = 0;
	int current_power;
	p2answer current_answer;

	// pre calculate our grid and just refer to it
	int *array = new int[height * width];
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			array[(y * width) + x] = calculate_pl(x, y, grid_serial);

	for (int square_size = 1; square_size < width + 1; square_size++)
		for (int x = 0; x < (width + 1 - square_size); x++)
			for (int y = 0; y < (height + 1 - square_size); y++)
			{
				// loop through offsets
				current_power = 0;
				for (int q = 0; q < square_size; q++)
					for (int w = 0; w < square_size; w++)
						current_power += array[(y * width) + (w * width) + x + q];

				if (current_power > highest_power)
				{
					highest_power = current_power;
					current_answer.x = x;
					current_answer.y = y;
					current_answer.ss = square_size;
				}
			}

	delete[] array;

	return current_answer;
}

typedef struct mtanswer
{
	int x, y, ss, power;
} mtanswer;

void mthread(int square_min, int square_max, int grid_serial, vector<mtanswer> *answers)
{
	int width = 300;
	int height = 300;
	int highest_power = 0;
	int current_power;
	mtanswer current_answer;

	// pre calculate our grid and just refer to it
	int *array = new int[height * width];
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			array[(y * width) + x] = calculate_pl(x, y, grid_serial);

	for (int square_size = square_min; square_size < square_max + 1; square_size++)
		for (int x = 0; x < (width + 1 - square_size); x++)
			for (int y = 0; y < (height + 1 - square_size); y++)
			{
				// loop through offsets
				current_power = 0;
				for (int q = 0; q < square_size; q++)
					for (int w = 0; w < square_size; w++)
						current_power += array[(y * width) + (w * width) + x + q];

				if (current_power > highest_power)
				{
					highest_power = current_power;
					current_answer.x = x;
					current_answer.y = y;
					current_answer.ss = square_size;
					current_answer.power = current_power;
				}
			}

	delete[] array;

	answers->push_back(current_answer);
}

int main()
{
	pair<int, int> answer = part1(7315);
	cout<<answer.first<<","<<answer.second<<endl;


	vector<mtanswer> answers;
	
	thread t1(mthread, 1, 75, 7315, &answers);
	thread t2(mthread, 76, 150, 7315, &answers);
	thread t3(mthread, 151, 225, 7315, &answers);
	thread t4(mthread, 226, 300, 7315, &answers);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	mtanswer winner;
	winner.power = 0;
	for (const auto &i: answers)
		if (i.power > winner.power)
		{
			winner.power = i.power;
			winner.x = i.x;
			winner.y = i.y;
			winner.ss = i.ss;
		}


	cout<<winner.x<<","<<winner.y<<","<<winner.ss<<endl;

	return 0;
}