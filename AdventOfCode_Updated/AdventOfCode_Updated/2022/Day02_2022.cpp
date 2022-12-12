#include <iostream>

#include "../2022/Day02_2022.h"

AOC22::Day02::Day02() : Day("Input//2022//day02_data.txt", "Input//2022//day02_data_simple.txt")
{

}

void AOC22::Day02::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	int score = 0;

	for (std::string row;input.NextRow(row);)
	{
		auto opponent = row[0] - 'A';
		auto me = row[2] - 'X';

		auto result = (opponent - me);

		if (result == 0) // Draw
		{
			score += 3 + me + 1;
		}
		else if (result == -2 || result == 1) // Loss
		{
			score += me + 1;
		}
		else if (result == -1 || result == 2) // Win
		{
			score += 6 + me + 1;
		}
	}

	printf("1) (%i)\n", score);
}

void AOC22::Day02::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	int score = 0;

	for (std::string row; input.NextRow(row);)
	{
		auto opponent = row[0] - 'A';
		auto outcome = row[2] - 'X' - 1; // -1 = loss, 0 = draw, 1 = win
		auto me = (opponent + outcome) % 3;
		
		if (me < 0)
		{
			me = 2;
		}

		if (outcome == -1) // Loss
		{
			score += me + 1;
		}
		else if (outcome == 0) // Draw
		{
			score += 3 + me + 1;
		}
		else if (outcome == 1) // Win
		{
			score += 6 + me + 1;
		}
	}

	printf("2) (%i)\n", score);
}

AOC22::Day02::~Day02()
{

}