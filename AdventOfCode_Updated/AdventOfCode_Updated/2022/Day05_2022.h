#pragma once
#include<vector>

#include "../Day.h"

namespace AOC22DAY05
{
	struct cargoArea
	{
		std::vector<std::vector<char>> cargoPiles;

		void CreatePiles(int);
		void Move(int, int, int);
		void AdvancedMove(int, int, int);
		void Add(int, char);
		std::string ToString();
	};
}

namespace AOC22
{
	class Day05 : public Day
	{
	private:
		struct AOC22DAY05::cargoArea cargoArea;
		void setUpCargo(std::vector<std::string>&);
	public:
		Day05();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day05();
	};
}
