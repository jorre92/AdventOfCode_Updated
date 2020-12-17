#include "Day01_2020.h"

AOC20::Day01::Day01() : Day("2020//Input//day01_data.txt", "2020//Input//day01_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day01::SolvePartOne(bool simpleData)
{
	auto stream = Day::Input(simpleData);
	
	std::vector<size_t> numbers;

	for (size_t firstNumber = 0; stream.Next(firstNumber); )
	{
		size_t secondNumber = 2020 - firstNumber;

		if (std::find(numbers.begin(), numbers.end(), secondNumber) != numbers.end())
		{
			printf("[%s-%s] : The product is {%d}.\n", _name.c_str(), __func__, secondNumber * firstNumber);
			break;
		}

		numbers.push_back(firstNumber);
	}
}

void AOC20::Day01::SolvePartTwo(bool simpleData)
{
	auto stream = Day::Input(simpleData);

	std::vector<size_t> numbers;
	size_t toReach = 2020;

	for (size_t firstNumber = 0; stream.Next(firstNumber); )
	{
		size_t left = toReach - firstNumber;

		for (size_t i = 0; i < numbers.size(); ++i)
		{
			size_t secondNumber = numbers[i];
			size_t thirdNumber = left - secondNumber;

			if (thirdNumber > 0)
			{
				if (std::find(numbers.begin(), numbers.end(), thirdNumber) != numbers.end())
				{
					printf("[%s-%s] : The product is {%d}.\n", _name.c_str(), __func__, thirdNumber * secondNumber * firstNumber);
					break;
				}
			}
		}

		numbers.push_back(firstNumber);
	}
}

AOC20::Day01::~Day01()
{
}
