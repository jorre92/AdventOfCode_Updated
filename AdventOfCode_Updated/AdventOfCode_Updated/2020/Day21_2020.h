#pragma once
#include "../Day.h"

namespace AOC20
{
	class Day21 : public Day
	{
	private:
		void SortMenuItems(const std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>&, const std::string&, std::vector<std::string>&, std::vector<std::string>&);
	public:
		Day21();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day21();
	};
}