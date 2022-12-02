#pragma once
#include "../Day.h"

namespace AOC20
{
	class Day18 : public Day
	{
	private:
		uint64_t NextValue(char**, bool = true);
		uint64_t Evaluate(char**, bool = true);
	public:
		Day18();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day18();
	};
}