#pragma once

#include "../Day.h"

namespace AOC22
{
	enum operation
	{
		Addition,
		Multiplication,
		Square
	};

	struct Monkey
	{
		size_t inspectedItems = 0;
		std::vector<uint64_t> items;
		AOC22::operation operation;
		std::string modifier;
		uint64_t testDivisible = 1;
		size_t throwToMonkeyIndexTrue = 0;
		size_t throwToMonkeyIndexFalse = 0;

		void InspectItems(std::vector<struct Monkey>& monkies, uint64_t div, uint64_t mod)
		{
			inspectedItems += items.size();
			while (items.size() > 0)
			{
				// do calc
				if (mod == 0)
				{
					items[0] = DoCalc(items[0]) / div;
				}
				else
				{
					items[0] = DoCalc(items[0]) % mod;
				}
				auto index = NextMonkeyIndex(items[0]);
				monkies[index].items.push_back(items[0]);
				items.erase(items.begin());
			}
		}

		uint64_t DoCalc(uint64_t temp)
		{
			uint64_t rhs = GetValue(modifier, temp);
			
			switch (operation)
			{
			case Addition:
				temp += rhs;
				break;
			case Multiplication:
				temp *= rhs;
				break;
			default:
				break;
			}

			return temp;
		}

		size_t NextMonkeyIndex(uint64_t temp)
		{
			return (temp % testDivisible) == 0 ? throwToMonkeyIndexTrue : throwToMonkeyIndexFalse;
		}

		uint64_t GetValue(const std::string& evaluate, uint64_t value)
		{
			if (evaluate == "old")
			{
				return value;
			}
			else
			{
				return std::stol(evaluate);
			}
		}
	};

	class Day11 : public Day
	{
	private:
		Monkey CreateMonkey(const std::vector<std::string>&);
	public:
		Day11();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day11();
	};
}
