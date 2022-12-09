#pragma once

#include "../Day.h"

namespace AOC22
{
	class Day08 : public Day
	{
	private:
		bool IsSeen(const std::vector<std::string>&, int, int);
		int SenicScore(const std::vector<std::string>&, int, int);
	public:
		Day08();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day08();
	};
}
