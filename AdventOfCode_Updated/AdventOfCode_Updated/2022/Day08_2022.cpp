#include <iostream>

#include "../2022/Day08_2022.h"

AOC22::Day08::Day08() : Day("Input//2022//day08_data.txt", "Input//2022//day08_data_simple.txt")
{
}

bool AOC22::Day08::IsSeen(const std::vector<std::string>& map, int xPos, int yPos)
{
	int min = 0;
	int maxY = map.size() - 1;
	int maxX = map[yPos].size() - 1;

	bool seen = true;

	// seen from top?
	for (int y = 0; y < yPos; y++)
	{
		if (map[y][xPos] >= map[yPos][xPos])
		{
			seen = false;
			break;
		}
	}

	if (seen)
	{
		return true;
	}
	seen = true;

	// seen from bot?
	for (int y = maxY; y > yPos; y--)
	{
		if (map[y][xPos] >= map[yPos][xPos])
		{
			seen = false;
			break;
		}
	}

	if (seen)
	{
		return true;
	}
	seen = true;

	// seen from left?
	for (int x = 0; x < xPos; x++)
	{
		if (map[yPos][x] >= map[yPos][xPos])
		{
			seen = false;
			break;
		}
	}

	if (seen)
	{
		return true;
	}
	seen = true;

	// seen from right?
	for (int x = maxX; x > xPos; x--)
	{
		if (map[yPos][x] >= map[yPos][xPos])
		{
			seen = false;
			break;
		}
	}

	return seen;
}

int AOC22::Day08::SenicScore(const std::vector<std::string>& map, int xPos, int yPos)
{
	int min = 0;
	int maxY = map.size() - 1;
	int maxX = map[yPos].size() - 1;
	char myTree = map[yPos][xPos];

	int upScore = 0, downScore = 0, leftScore = 0, rightScore = 0;

	// seen number of trees up
	for (int y = yPos - 1; y >= 0; y--)
	{
		upScore++;

		if (map[y][xPos] >= myTree)
		{
			break;
		}
	}

	// seen number of trees down
	for (int y = yPos + 1; y <= maxY; y++)
	{
		downScore++;

		if (map[y][xPos] >= myTree)
		{
			break;
		}
	}

	// seen number of trees left
	for (int x = xPos-1; x >= 0; x--)
	{
		leftScore++;

		if (map[yPos][x] >= myTree)
		{
			break;
		}
	}

	// seen number of trees right
	for (int x = xPos + 1; x <= maxX; x++)
	{
		rightScore++;

		if (map[yPos][x] >= myTree)
		{
			break;
		}
	}

	return upScore * downScore * leftScore * rightScore;
}

void AOC22::Day08::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<std::string> mapStrings;
	
	if (input.NextBatch(mapStrings))
	{
		int treesICanSee = 0;

		for (int y = 0; y < mapStrings.size(); y++)
		{
			for (int x = 0; x < mapStrings[y].size(); x++)
			{
				if (IsSeen(mapStrings, x, y))
				{
					treesICanSee++;
				}
			}
		}

		std::cout << treesICanSee << std::endl;
	}

}

void AOC22::Day08::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<std::string> mapStrings;

	if (input.NextBatch(mapStrings))
	{
		int highestScore = 0;

		for (int y = 0; y < mapStrings.size(); y++)
		{
			for (int x = 0; x < mapStrings[y].size(); x++)
			{
				auto score = SenicScore(mapStrings, x, y);

				highestScore = score > highestScore ? score : highestScore;
			}
		}

		std::cout << highestScore << std::endl;
	}
}

AOC22::Day08::~Day08()
{
}