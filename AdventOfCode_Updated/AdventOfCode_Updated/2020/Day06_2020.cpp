#include "Day06_2020.h"
#include <map>

AOC20::Day06::Day06() : Day("2020//Input//day06_data.txt", "2020//Input//day06_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day06::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);
	std::map<char, int> answers;

	int totalYes = 0;

	for (std::string groupAnswers; input.NextBatch(groupAnswers);)
	{
		std::string yesAnswers = "";

		for (char c : groupAnswers)
		{
			if (yesAnswers.find(c) == std::string::npos && c != '\n')
			{
				yesAnswers += c;
			}
		}

		totalYes += yesAnswers.size();
	}

	printf("[%s-%s] : Total number yes {%d}.\n", _name.c_str(), __func__, totalYes);
}

void AOC20::Day06::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);
	std::map<char, int> answers;

	int totalAgreedOn = 0;

	for (std::vector<std::string> groupAnswers; input.NextBatch(groupAnswers);)
	{
		std::string agreedOn = groupAnswers[0];

		for (int i = 1; i < groupAnswers.size(); ++i)
		{
			std::string agreed;

			for (char c : agreedOn)
			{
				if (groupAnswers[i].find(c) != std::string::npos && agreed.find(c) == std::string::npos)
				{
					agreed += c;
				}
			}

			agreedOn = agreed;
		}
		totalAgreedOn += agreedOn.length();
	}

	printf("[%s-%s] : Total agreed on yes {%d}.\n", _name.c_str(), __func__, totalAgreedOn);
}

AOC20::Day06::~Day06()
{
}