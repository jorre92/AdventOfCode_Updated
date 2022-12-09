#include <iostream>

#include "../2022/Day09_2022.h"

AOC22::Day09::Day09() : Day("Input//2022//day09_data.txt", "Input//2022//day09_data_simple.txt")
{
}


void AOC22::Day09::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);
	std::string row;

	Snake snake(1);

	for (; input.NextRow(row);)
	{
		auto partOne = row.substr(0, row.find(' '))[0];
		auto partTwo = std::stoi(row.substr(row.find(' ') + 1));

		Position dir;

		switch (partOne)
		{
		case 'R':
			dir.X = 1;
			break;
		case 'L':
			dir.X = -1;
			break;
		case 'U':
			dir.Y = -1;
			break;
		case 'D':
			dir.Y = 1;
			break;
		default:
			break;
		}

		for (int i = 0; i < partTwo; ++i)
		{
			snake.Move(dir);
		}
	}

	std::cout << snake.body[snake.body.size() - 1].history.size() << std::endl;
}

void AOC22::Day09::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);
	std::string row;

	Snake snake(9);

	for (; input.NextRow(row);)
	{
		auto partOne = row.substr(0, row.find(' '))[0];
		auto partTwo = std::stoi(row.substr(row.find(' ') + 1));

		Position dir;

		switch (partOne)
		{
		case 'R':
			dir.X = 1;
			break;
		case 'L':
			dir.X = -1;
			break;
		case 'U':
			dir.Y = -1;
			break;
		case 'D':
			dir.Y = 1;
			break;
		default:
			break;
		}

		for (int i = 0; i < partTwo; ++i)
		{
			snake.Move(dir);
		}
	}

	std::cout << snake.body[snake.body.size()-1].history.size() << std::endl;
}

AOC22::Day09::~Day09()
{
}