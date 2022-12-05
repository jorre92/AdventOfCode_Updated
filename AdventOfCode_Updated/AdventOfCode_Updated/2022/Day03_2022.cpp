#include <iostream>
#include <cctype>

#include "../2022/Day03_2022.h"

AOC22::Day03::Day03() : Day("Input//2022//day03_data.txt", "Input//2022//day03_data_simple.txt")
{

}

bool AOC22::Day03::commonChar(const std::string& firstComponent, const std::string& secondComponent, char& commonChar)
{
	for (size_t i = 0; i < firstComponent.size(); ++i)
	{
		auto found = secondComponent.find(firstComponent[i]);

		if (found != -1)
		{
			commonChar = secondComponent[found];
			break;
		}
	}

	return true;
}

bool AOC22::Day03::commonChars(const std::string& firstComponent, const std::string& secondComponent, std::string& commonChars)
{

	for (size_t i = 0; i < firstComponent.size(); ++i)
	{
		auto found = secondComponent.find(firstComponent[i]);

		if (found != -1)
		{
			commonChars += secondComponent[found];
		}
	}
	return true;
}

size_t AOC22::Day03::Score(const char& character)
{
	size_t score = 0;

	if (std::islower(character))
	{
		score = character - 'a' + 1;
	}
	else
	{
		score = character - 'A' + 27;
	}

	return score;
}

void AOC22::Day03::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	size_t score = 0;

	for (std::string row; input.NextRow(row);)
	{
		auto firstItem = row.substr(0, row.size()/2);
		auto secondItem = row.substr(row.size() / 2);
		char common;

		commonChar(firstItem, secondItem, common);
		score += Score(common);
	}

	std::cout << score << std::endl;
}

void AOC22::Day03::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);
	size_t score = 0;

	for (std::string first; input.NextRow(first);)
	{
		std::string second, third;

		if (input.NextRow(second) && input.NextRow(third))
		{
			std::string matched = "";
			char group;
			commonChars(first, second, matched);
			commonChar(matched, third, group);

			score += Score(group);

		}
	}

	std::cout << score << std::endl;
}

AOC22::Day03::~Day03()
{

}