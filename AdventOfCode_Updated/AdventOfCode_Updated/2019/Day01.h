#pragma once
#include "../Day.h"

namespace AOC19
{
	class Day01 : public Day
	{
	private:
		int FuleNeeded(int);
	public:
		Day01();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day01();
	};
}
