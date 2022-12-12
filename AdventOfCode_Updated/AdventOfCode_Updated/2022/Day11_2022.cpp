#include <iostream>
#include <algorithm>

#include "../2022/Day11_2022.h"
#include "../RegularExpressions.h"

AOC22::Day11::Day11() : Day("Input//2022//day11_data.txt", "Input//2022//day11_data_simple.txt")
{
}

AOC22::Monkey AOC22::Day11::CreateMonkey(const std::vector<std::string>& batch)
{
	std::vector<std::string> results;
	std::string result;

	Monkey newMonkey;

	AOCCORE::RegularExpressions::RunIteratorSearch(batch[1], "-?[0-9]+", results);
		
	for (auto result : results)
	{
		newMonkey.items.push_back(std::stoi(result));
	}
	auto modifyString = batch[2].substr(batch[2].find("old ") + 4);

	if (modifyString[0] == '*')
	{
		newMonkey.operation = AOC22::Multiplication;
	}
	else
	{
		newMonkey.operation = AOC22::Addition;
	}

	newMonkey.modifier = modifyString.substr(2);
	AOCCORE::RegularExpressions::RunSearch(batch[3], "-?[0-9]+", result);
	newMonkey.testDivisible = std::stoi(result);
	newMonkey.throwToMonkeyIndexTrue = std::stoi(batch[4].substr(batch[4].find_last_of(' ')+1));
	newMonkey.throwToMonkeyIndexFalse = std::stoi(batch[5].substr(batch[5].find_last_of(' ')+1));

	return newMonkey;
}

void AOC22::Day11::SolvePartOne(bool simple)
{
	uint64_t mod = 1;
	auto input = Day::Input(simple);

	std::vector<Monkey> monkeys;
	
	// create all monkeys
	for (std::vector<std::string> batch; input.NextBatch(batch);)
	{
		auto m = CreateMonkey(batch);
		monkeys.push_back(m);
		mod *= m.testDivisible;
	}

	for (size_t i = 0; i < 20; ++i)
	{
		for (auto& m : monkeys)
		{
			m.InspectItems(monkeys, 3, 0);
		}
	}
	
	std::vector<size_t> monkeyBusiness;
	for (auto m : monkeys)
	{
		monkeyBusiness.push_back(m.inspectedItems);
		printf("Items inspected : %llu\n", m.inspectedItems);
	}

	std::sort(monkeyBusiness.begin(), monkeyBusiness.end(), std::greater<size_t>());

	std::cout << monkeyBusiness[0] * monkeyBusiness[1] << std::endl;
}

void AOC22::Day11::SolvePartTwo(bool simple)
{
	uint64_t mod = 1;
	auto input = Day::Input(simple);

	std::vector<Monkey> monkeys;

	// create all monkeys
	for (std::vector<std::string> batch; input.NextBatch(batch);)
	{
		auto m = CreateMonkey(batch);
		monkeys.push_back(m);
		mod *= m.testDivisible;
	}

	for (size_t i = 0; i < 10000; ++i)
	{
		for (auto& m : monkeys)
		{
			m.InspectItems(monkeys, 1, mod);
		}
	}

	std::vector<size_t> monkeyBusiness;
	for (auto m : monkeys)
	{
		monkeyBusiness.push_back(m.inspectedItems);
		printf("Items inspected : %llu\n", m.inspectedItems);
	}

	std::sort(monkeyBusiness.begin(), monkeyBusiness.end(), std::greater<size_t>());

	std::cout << monkeyBusiness[0] * monkeyBusiness[1] << std::endl;
}

AOC22::Day11::~Day11()
{
}