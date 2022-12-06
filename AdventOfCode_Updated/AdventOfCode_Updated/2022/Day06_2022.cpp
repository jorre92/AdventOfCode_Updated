#include <iostream>
#include <algorithm>

#include "../2022/Day06_2022.h"

AOC22::Day06::Day06() : Day("Input//2022//day06_data.txt", "Input//2022//day06_data_simple.txt")
{
	
}

bool AOC22::Day06::isUnique(const std::string& list)
{
	std::string unique = list;

	std::sort(unique.begin(), unique.end());

	for (size_t i = 0; i < unique.length() - 1; i++)
	{
		if (unique[i] == unique[i + 1])
		{
			return false;
		}
	}
	return true;
}

void AOC22::Day06::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::string datastream;
	input.NextRow(datastream);

	for (size_t markerPoint = 0; markerPoint < datastream.size() - 3; markerPoint++)
	{
		std::string markerCheck = datastream.substr(markerPoint, 4);

		if (isUnique(markerCheck))
		{
			std::cout << markerCheck << std::endl;
			std::cout << markerPoint + 4 << std::endl;
			break;
		}
	}
}


void AOC22::Day06::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	std::string datastream;
	input.NextRow(datastream);

	for (size_t markerPoint = 0; markerPoint < datastream.size() - 14; markerPoint++)
	{
		std::string markerCheck = datastream.substr(markerPoint, 14);

		if (isUnique(markerCheck))
		{
			std::cout << markerCheck << std::endl;
			std::cout << markerPoint + 14 << std::endl;
			break;
		}
	}
}

AOC22::Day06::~Day06()
{
}