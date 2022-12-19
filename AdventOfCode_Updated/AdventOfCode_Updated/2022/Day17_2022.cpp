#include "../2022/Day17_2022.h"



void AOC22::Day17::PrintMap(const PointMap& map, TetrisBlock& block, int highestPoint)
{
	system("CLS");
	for (int y = highestPoint; y >= 0; y--)
	{
		for (int x = 0; x <= 8; x++)
		{
			Point p(x, y);
			
			if (x == 0 ||x == 8)
			{
				printf("|");
			}
			else if (map.find(p) != map.end())
			{
				printf("#");
			}
			else if (block.Contains(p))
			{
				printf("@");
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}
}

AOC22::Day17::Day17() : Day("Input//2022//day17_data.txt", "Input//2022//day17_data_simple.txt")
{
}

void AOC22::Day17::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<AOC22::TetrisBlock> blocks;
	blocks.push_back(AOC22::TetrisBlock("####"));
	blocks.push_back(AOC22::TetrisBlock(".#.\n###\n.#."));
	blocks.push_back(AOC22::TetrisBlock("..#\n..#\n###"));
	blocks.push_back(AOC22::TetrisBlock("#\n#\n#\n#"));
	blocks.push_back(AOC22::TetrisBlock("##\n##"));
	std::string commands;

	input.NextRow(commands);
	
	PointMap map;
	// create floor
	for (int i = -1; i < 8; i++)
	{
		map[Point(i, 0)] = true;
	}
	size_t highestPoint = 0;
	size_t itteration = 0;
	for (int i = 0; i < 2022; i++)
	{
		AOC22::TetrisBlock nextBlock = blocks[i % blocks.size()];
		nextBlock.Move(Point(3, nextBlock.height + highestPoint + 3));

		while (true)
		{
			auto command = commands[itteration];
			Point Dir = command == '<' ? Point(-1, 0) : Point(1, 0);
			itteration++;
			itteration %= commands.size();

			if (nextBlock.CanMove(map, Dir))
			{
				nextBlock.Move(Dir);
			}

			if (nextBlock.CanMove(map, Point(0, -1)))
			{
				nextBlock.Move(Point(0, -1));
			}
			else
			{
				auto blocksHighestPoint = nextBlock.LockBlock(map);
				highestPoint = std::max(blocksHighestPoint, highestPoint);
				break;
			}
		}
	}

	printf("1) (%i)\n", highestPoint);
}

void AOC22::Day17::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);
	std::vector<AOC22::TetrisBlock> blocks;
	blocks.push_back(AOC22::TetrisBlock("####"));
	blocks.push_back(AOC22::TetrisBlock(".#.\n###\n.#."));
	blocks.push_back(AOC22::TetrisBlock("..#\n..#\n###"));
	blocks.push_back(AOC22::TetrisBlock("#\n#\n#\n#"));
	blocks.push_back(AOC22::TetrisBlock("##\n##"));
	std::string commands;

	input.NextRow(commands);

	auto variable = commands.size() * blocks.size();

	PointMap map;
	// create floor
	for (int i = -1; i < 8; i++)
	{
		map[Point(i, 0)] = true;
	}
	size_t highestPoint = 0;
	size_t itteration = 0;
	size_t total = 1000000000000;

	for (size_t i = 0; i < total; i++)
	{
		AOC22::TetrisBlock nextBlock = blocks[i % blocks.size()];
		nextBlock.Move(Point(3, nextBlock.height + highestPoint + 3));

		while (true)
		{
			auto command = commands[itteration];
			Point Dir = command == '<' ? Point(-1, 0) : Point(1, 0);
			itteration += 1;
			itteration %= commands.size();



			if (nextBlock.CanMove(map, Dir))
			{
				nextBlock.Move(Dir);
			}

			if (nextBlock.CanMove(map, Point(0, -1)))
			{
				nextBlock.Move(Point(0, -1));
			}

			if (nextBlock.CanMove(map, Point(0, -1)))
			{
				auto blocksHighestPoint = nextBlock.LockBlock(map);
					highestPoint = std::max(blocksHighestPoint, highestPoint);
					break;
			}
		}
	}

	printf("2) (%llu)\n", highestPoint);
}

AOC22::Day17::~Day17()
{

}
