#include <iostream>

#include "../2022/Day04_2022.h"

AOC22::Day04::Day04() : Day("Input//2022//day04_data.txt", "Input//2022//day04_data_simple.txt")
{

}

void AOC22::Day04::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	size_t score = 0;

	for (std::string row; input.NextRow(row);)
	{
		auto part1 = row.substr(0, row.find(','));
		auto part2 = row.substr(row.find(',') + 1);

		auto lowFirst = atoi(part1.substr(0, part1.find('-')).c_str());
		auto highFirst = atoi(part1.substr(part1.find('-') + 1).c_str());
		auto lowSecond = atoi(part2.substr(0, part2.find('-')).c_str());
		auto highSecond = atoi(part2.substr(part2.find('-') + 1).c_str());

		if ((lowFirst <= lowSecond && highFirst >= highSecond) || (lowFirst >= lowSecond && highFirst <= highSecond))
		{
			++score;
		}
	}

	std::cout << score << std::endl;
}

void AOC22::Day04::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	size_t score = 0;

	for (std::string row; input.NextRow(row);)
	{
		auto part1 = row.substr(0, row.find(','));
		auto part2 = row.substr(row.find(',') + 1);

		auto lowFirst = atoi(part1.substr(0, part1.find('-')).c_str());
		auto highFirst = atoi(part1.substr(part1.find('-') + 1).c_str());
		auto lowSecond = atoi(part2.substr(0, part2.find('-')).c_str());
		auto highSecond = atoi(part2.substr(part2.find('-') + 1).c_str());

		if (!(lowFirst > highSecond || lowSecond > highFirst))
		{
			score++;
		}
	}

	std::cout << score << std::endl;
}

AOC22::Day04::~Day04()
{

}