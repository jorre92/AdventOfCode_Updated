#pragma once
#include "../Day.h"

namespace AOC22
{
	class Day03 : public Day
	{
	private:
		bool commonChar(const std::string&, const std::string&, char&);
		bool commonChars(const std::string&, const std::string&, std::string&);
		size_t Score(const char&);
	public:
		Day03();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day03();
	};
}