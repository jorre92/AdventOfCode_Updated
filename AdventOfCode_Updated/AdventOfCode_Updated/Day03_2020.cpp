#include "Day03_2020.h"

bool AOC20::Day03::HitTree(size_t x , const std::string& map) const
{
	return map[x % map.size()] == '#';
}

AOC20::Day03::Day03() : Day("2020//Input//day03_data.txt", "2020//Input//day03_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day03::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);
	
	std::pair <size_t, size_t> direction(3, 1);
	std::string s;
	size_t treeHit = 0;

	for (int i = 0; input.NextRow(s); ++i)
	{
		if (HitTree(direction.first * i, s))
		{
			treeHit++;
		}
	}

	printf("[%s-%s] : Tree collisions {%d}.\n", _name.c_str(), __func__, treeHit);
}

void AOC20::Day03::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);

	std::vector<std::pair<size_t, size_t>> directions
	{ 
		std::pair<size_t, size_t>(1, 1),
		std::pair<size_t, size_t>(3, 1),
		std::pair<size_t, size_t>(5, 1),
		std::pair<size_t, size_t>(7, 1),
		std::pair<size_t, size_t>(1, 2) 
	};
	std::vector<uint64_t> treeHits{ 0, 0, 0, 0, 0 };

	std::string s;

	for (int i = 0; input.NextRow(s); ++i)
	{
		for (int direction = 0; direction < directions.size(); ++direction)
		{
			if (i % directions[direction].second == 0 && HitTree((directions[direction].first * i) / directions[direction].second, s))
			{
				treeHits[direction]++;
			}
		}
	}

	uint64_t product = 1;

	for (auto hits : treeHits)
	{
		product *= hits;
	}

	printf("[%s-%s] : Tree collisions {%llu}.\n", _name.c_str(), __func__, product);
}

AOC20::Day03::~Day03()
{
}