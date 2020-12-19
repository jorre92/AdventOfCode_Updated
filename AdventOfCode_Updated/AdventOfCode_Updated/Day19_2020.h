#pragma once
#include "Day.h"
#include <map>

namespace AOC20
{
	class Day19 : public Day
	{
	private:

		std::string GenerateRegEx(size_t, std::map<size_t, std::string>&, bool = false);
	public:
		Day19();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day19();
	};
}