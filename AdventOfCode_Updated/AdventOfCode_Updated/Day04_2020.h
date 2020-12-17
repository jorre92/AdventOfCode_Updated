#pragma once
#include "Day.h"

namespace AOC20
{
	class Day04 : public Day
	{
	private:
		std::vector<std::string> _requredFields;
		bool ValidateData(size_t, const std::string&) const;
	public:
		Day04();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day04();
	};
}
