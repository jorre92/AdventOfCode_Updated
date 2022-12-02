#pragma once
#include "../Day.h"

namespace AOC20
{
	class Day05 : public Day
	{
	private:
		constexpr int Power(int n, int p);
	public:
		Day05();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day05();
	};
}