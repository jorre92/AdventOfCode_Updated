#pragma once
#include "../Day.h"
#include "../Deck.h"

namespace AOC20
{
	class Day22 : public Day
	{
	private:
		int RecursiveCombat(std::vector<Deck>, std::vector<Deck>&) const;
	public:
		Day22();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day22();
	};
}