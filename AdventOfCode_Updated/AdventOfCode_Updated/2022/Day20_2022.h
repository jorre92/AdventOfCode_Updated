#pragma once

#include "../Day.h"

namespace AOC22
{
	struct Day20Item
	{
		long long int Id;
		long long int Value;

		bool operator==(const Day20Item& other) const { return this->Id == other.Id; }
	};

	class Day20 : public Day
	{
	private:
		void Decode(const std::vector<Day20Item>&, std::vector<Day20Item>&);
	public:
		Day20();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day20();
	};
}
