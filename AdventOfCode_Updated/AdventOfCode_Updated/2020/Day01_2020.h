#pragma once
#include "../Day.h"

namespace AOC20
{
	class Day01 : public Day
	{
	public:
		Day01();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day01();
	};
}