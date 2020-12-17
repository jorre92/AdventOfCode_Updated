#pragma once
#include "Day.h"

namespace AOC20
{
	class Day03 : public Day
	{
	private:
		bool HitTree(size_t, const std::string&) const;
	public:
		Day03();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day03();
	};
}


