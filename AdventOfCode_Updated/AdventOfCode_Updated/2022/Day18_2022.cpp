#include "../2022/Day18_2022.h"
#include "../RegularExpressions.h"

AOC22::Day18::Day18() : Day("Input//2022//day18_data.txt", "Input//2022//day18_data_simple.txt")
{
}

void AOC22::Day18::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<AOC22::Day18Cube> cubes;
	size_t area = 0;

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> results;
		auto index = row.find(',');
		int x = std::stoi(row.substr(0, index));
		int y = std::stoi(row.substr(index+1, row.find_last_of(',')));
		int z = std::stoi(row.substr(row.find_last_of(',')+1));

		AOC22::Day18Cube cube(x, y, z);

		auto n = cube.NumberOfNeighbours(cubes);

		area -= n;
		area += 6 - static_cast<unsigned long long>(n);

		cubes.push_back(cube);
	}
	
	printf("1) (%llu)\n", area);
}

void AOC22::Day18::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<AOC22::Day18Cube> cubes;

	int xMin = 1000;
	int yMin = 1000;
	int zMin = 1000;
	int xMax = 0;
	int yMax = 0;
	int zMax = 0;

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> results;
		auto index = row.find(',');
		int x = std::stoi(row.substr(0, index));
		int y = std::stoi(row.substr(index + 1, row.find_last_of(',')));
		int z = std::stoi(row.substr(row.find_last_of(',') + 1));

		xMin = std::min(x, xMin);
		yMin = std::min(y, yMin);
		zMin = std::min(z, zMin);

		xMax = std::max(x, xMax);
		yMax = std::max(y, yMax);
		zMax = std::max(z, zMax);

		AOC22::Day18Cube cube(x, y, z);

		cubes.push_back(cube);
	}
	xMin--;
	yMin--;
	zMin--;
	xMax++;
	yMax++;
	zMax++;

	std::vector<AOC22::Day18Cube> water;
	std::vector<AOC22::Day18Cube> UsedWater;
	water.push_back(AOC22::Day18Cube::Day18Cube(xMin,yMin,zMin));
	size_t area = 0;
	
	while (!water.empty())
	{
		auto neighbours = water[0].GetNeighbours();

		for (auto& n : neighbours)
		{
			
			if (std::find(UsedWater.begin(), UsedWater.end(), n) != UsedWater.end())
			{
				// do nothing.
			}
			else if (n.X > xMax || n.X < xMin || n.Y > yMax || n.Y < yMin || n.Z > zMax || n.Z < zMin)
			{
				// do nothing.
			}
			else if(std::find(cubes.begin(), cubes.end(), n) != cubes.end())
			{
				area++;
			}
			else if (std::find(water.begin(), water.end(), n) == water.end())
			{
				water.push_back(n);
			}
		}
		UsedWater.push_back(water[0]);
		water.erase(water.begin());
	}
	printf("2) (%llu)\n", area);
}

AOC22::Day18::~Day18()
{

}
