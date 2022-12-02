#include "../2022/Day01_2022.h"

AOC22::Day01::Day01() : Day("Input//2022//day01_data.txt", "Input//2022//day01_data_simple.txt")
{
	this->_name = __func__;
}

void AOC22::Day01::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<size_t> calories;
	std::string row = "";
	size_t totalCalories = 0;

	for (size_t value = 0; input.NextRow(row);)
	{
		std::printf(row.c_str());
	}
}