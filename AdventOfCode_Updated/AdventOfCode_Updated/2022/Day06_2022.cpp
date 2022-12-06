#include <iostream>
#include <algorithm>

#include "../2022/Day06_2022.h"

AOC22::Day06::Day06() : Day("Input//2022//day06_data.txt", "Input//2022//day06_data_simple.txt")
{
	
}

void AOC22::Day06::findMarker(const std::string& dataStream, size_t messageSize)
{
	for (size_t markerPoint = 0; markerPoint < dataStream.size() - messageSize - 1; markerPoint++)
	{
		std::string markerCheck = dataStream.substr(markerPoint, messageSize);

		if (isUnique(markerCheck))
		{
			std::cout << markerCheck << std::endl;
			std::cout << markerPoint + messageSize << std::endl;
			break;
		}
	}
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

	findMarker(datastream, 4);
}


void AOC22::Day06::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	std::string datastream;
	input.NextRow(datastream);

	findMarker(datastream, 14);
}

AOC22::Day06::~Day06()
{
}