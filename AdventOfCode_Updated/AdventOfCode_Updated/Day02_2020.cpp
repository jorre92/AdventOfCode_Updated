#include "Day02_2020.h"
#include "RegularExpressions.h"

AOC20::Day02::Day02() : Day("2020//Input//day02_data.txt", "2020//Input//day02_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day02::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);
	int validPasswords = 0;

	for (std::string s; input.NextRow(s);)
	{
		std::vector<std::string> parsed;

		if (AOCCORE::RegularExpressions::RunSearch(s, "([0-9]*)-([0-9]*) ([a-z]|[A-Z]): (.*)", parsed))
		{
			size_t min = std::stoi(parsed[1]);
			size_t max = std::stoi(parsed[2]);
			char c = parsed[3][0];
			auto password = parsed[4];
			int count = std::count(password.begin(), password.end(), c);

			if (count <= max && count >= min)
			{
				validPasswords++;
			}
		}
	}

	printf("[%s-%s] : Valid passwords {%d}.\n", _name.c_str(), __func__, validPasswords);
}

void AOC20::Day02::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);
	int validPasswords = 0;

	for (std::string s; input.NextRow(s);)
	{
		std::vector<std::string> parsed;

		if (AOCCORE::RegularExpressions::RunSearch(s, "([0-9]*)-([0-9]*) ([a-z]|[A-Z]): (.*)", parsed))
		{
			size_t first = std::stoi(parsed[1]);
			size_t second = std::stoi(parsed[2]);
			char c = parsed[3][0];
			auto password = parsed[4];

			if ((password[first-1] == c) != (password[second-1] == c))
			{
				validPasswords++;
			}
		}
	}

	printf("[%s-%s] : Valid passwords {%d}.\n", _name.c_str(), __func__, validPasswords);
}

AOC20::Day02::~Day02()
{
}
