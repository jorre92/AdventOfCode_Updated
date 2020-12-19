#include "Day19_2020.h"
#include "RegularExpressions.h"

#include <map>

std::string AOC20::Day19::GenerateRegEx(size_t start, std::map<size_t, std::string>& rules, bool partTwo)
{
	std::string rule;

	rule = rules[start];

	char* index = &rule[0];
	bool seen8 = false;
	bool seen11 = false;
	while (true)
	{
		switch (*index)
		{
		case '\"':
			index++;
			index++;
			index++;
			break;
		case ' ':
		case '(':
		case ')':
		case '|':
			index++;
			break;
		case '\0':
			rule.erase(std::remove(rule.begin(), rule.end(), '\"'), rule.end());
			rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
			return rule;
		default:
		{
			size_t move;
			std::string toAdd;
			auto ruleNr = std::stoi(index, &move);

			if (partTwo)
			{
				if (ruleNr == 8)
				{
					if(seen8)
					{
						index += 1;
						break;
					}
					seen8 = true;
				}
				else if (ruleNr == 11)
				{
					if (seen11)
					{
						index += 2;
						break;
					}
					seen11 = true;
				}
			}

			if (rules[ruleNr].find('|') != std::string::npos)
			{
				toAdd = "(" + rules[ruleNr] + ")";
			}
			else
			{
				toAdd = rules[ruleNr];
			}

			auto valid = index - &rule[0];
			rule.erase(valid, move);
			rule.insert(valid, toAdd);

			index = &rule[valid];
		}
			break;
		}
	}

	return rule;
}

AOC20::Day19::Day19() : Day("2020//Input//day19_data.txt", "2020//Input//day19_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day19::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);
	std::vector<std::string> batch;
	std::vector<std::string> messages;
	std::map<size_t, std::string> regExRule;

	if (!input.NextBatch(batch)) { return; }

	for (auto& rule : batch)
	{
		std::vector<std::string> results;
		AOCCORE::RegularExpressions::RunSearch(rule, "([0-9]+): (.*)", results);
		size_t index = std::stoul(results[1]);
		regExRule[index] = results[2];
		rule.erase(std::remove(rule.begin(), rule.end(), '\"'), rule.end());
	}

	auto regEx = GenerateRegEx(0, regExRule);
	auto matching = 0;
	for(std::string row; input.NextRow(row);)
	{
		std::vector<std::string> results;
		if (AOCCORE::RegularExpressions::RunSearch(row, regEx, results) && results[0].length() == row.length())
		{
			matching++;
		}
	}

	printf("[%s-%s] : Number of matching messages {%d} .\n", _name.c_str(), __func__, matching);
}

void AOC20::Day19::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);
	std::vector<std::string> batch;
	std::vector<std::string> messages;
	std::map<size_t, std::string> regExRule;

	if (!input.NextBatch(batch)) { return; }

	for (auto& rule : batch)
	{
		std::vector<std::string> results;
		AOCCORE::RegularExpressions::RunSearch(rule, "([0-9]+): (.*)", results);
		size_t index = std::stoul(results[1]);
		regExRule[index] = results[2];
		rule.erase(std::remove(rule.begin(), rule.end(), '\"'), rule.end());
	}

	auto temp = "8 11";
	regExRule[8] = "42 | 42 8";
	regExRule[11] = "42 31 | 42 11 31";

	auto regExTouse = GenerateRegEx(0, regExRule, true);
	auto replaceIndex = regExTouse.find('8');
	if (replaceIndex != std::string::npos)
	{
		regExTouse.erase(replaceIndex, 1);
		regExTouse.insert(replaceIndex, "(\\w+)");

	}
	replaceIndex = regExTouse.find('11');
	if (replaceIndex != std::string::npos)
	{
		regExTouse.erase(replaceIndex, 2);
		regExTouse.insert(replaceIndex, "(\\w+)");
	}

	auto matching = 0;
	for (std::string row; input.NextRow(row);)
	{
		auto copy = row;
		std::vector<std::string> results;
		if (AOCCORE::RegularExpressions::RunSearch(row, regExTouse, results))
		{
			matching++;
		}
			
	}

	printf("[%s-%s] : Number of matching messages {%d} .\n", _name.c_str(), __func__, matching);
}

AOC20::Day19::~Day19()
{
}