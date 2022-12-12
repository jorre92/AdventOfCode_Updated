#include <iostream>
#include <algorithm>

#include "../2022/Day01_2022.h"

AOC22::Day01::Day01() : Day("Input//2022//day01_data.txt", "Input//2022//day01_data_simple.txt")
{
	this->_name = __func__;
}

void AOC22::Day01::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	int mostCalories = 0;

	for (struct { std::string row; int totalCalories; } data { "",  0 }; input.NextRow(data.row);)
	{
		if (data.row.empty())
		{
			if (data.totalCalories > mostCalories)
			{
				mostCalories = data.totalCalories;
			}
			data.totalCalories = 0;
		}
		else
		{
			auto calories = std::atoi(data.row.c_str());

			data.totalCalories += calories;
		}
	}

	printf("1) (%i)\n", mostCalories);
}

void AOC22::Day01::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<int> caloriesPerElf;
	std::string row;
	int totalCalories = 0;

	while (input.NextRow(row))
	{
		if (row.empty())
		{
			caloriesPerElf.push_back(totalCalories);
			totalCalories = 0;
		}
		else
		{
			auto calories = std::atoi(row.c_str());
			totalCalories += calories;
		}
	}
	caloriesPerElf.push_back(totalCalories);

	std::sort(caloriesPerElf.begin(), caloriesPerElf.end(), std::greater<int>());

	auto topThreeCalories = caloriesPerElf[0] + caloriesPerElf[1] + caloriesPerElf[2];

	printf("2) (%i)\n", topThreeCalories);
}

AOC22::Day01::~Day01()
{

}