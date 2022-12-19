#pragma once

#include "../Day.h"

namespace AOC22
{
	struct Day18Cube
	{
		int X = 0;
		int Y = 0;
		int Z = 0;

		Day18Cube(int x, int y, int z) : X(x), Y(y), Z(z)
		{

		}

		int NumberOfNeighbours(const std::vector<Day18Cube>& cubes)
		{
			int neighbours = 0;

			for (auto& n : GetNeighbours())
			{
				if (std::find(cubes.begin(), cubes.end(), n) != cubes.end())
				{
					neighbours += 1;
				}
			}

			return neighbours;
		}

		std::vector<Day18Cube> GetNeighbours()
		{
			std::vector<Day18Cube> neighbours;

			neighbours.push_back(Day18Cube(this->X + 1, this->Y, this->Z));
			neighbours.push_back(Day18Cube(this->X - 1, this->Y, this->Z));
			neighbours.push_back(Day18Cube(this->X, this->Y + 1, this->Z));
			neighbours.push_back(Day18Cube(this->X, this->Y - 1, this->Z));
			neighbours.push_back(Day18Cube(this->X, this->Y, this->Z + 1));
			neighbours.push_back(Day18Cube(this->X, this->Y, this->Z - 1));

			return neighbours;
		}

		bool operator== (const Day18Cube& other) const
		{
			return (this->X == other.X) && (this->Y == other.Y) && (this->Z == other.Z);
		}
	};

	class Day18 : public Day
	{
	private:
	public:
		Day18();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day18();
	};
}
