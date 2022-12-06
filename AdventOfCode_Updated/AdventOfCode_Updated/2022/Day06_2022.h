#pragma once

#include "../Day.h"

namespace AOC22
{
	class Day06 : public Day
	{
	private:
		bool isUnique(const std::string&);
	public:
		Day06();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day06();
	};
}
