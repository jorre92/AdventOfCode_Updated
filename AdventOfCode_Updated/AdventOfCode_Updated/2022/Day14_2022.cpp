#include <algorithm>

#include "../2022/Day14_2022.h"
#include "../RegularExpressions.h"

AOC22::Day14::Day14() : Day("Input//2022//day14_data.txt", "Input//2022//day14_data_simple.txt")
{
}

void AOC22::Day14::CalculateMaxSize(PointMap& rocks, PointMap& sand)
{
	for (auto& rock : rocks)
	{
		if (rock.first.X > this->MaxX)
		{
			this->MaxX = rock.first.X;
		}
		if (rock.first.X < this->MinX)
		{
			this->MinX = rock.first.X;
		}
		if (rock.first.Y > this->MaxY)
		{
			this->MaxY = rock.first.Y;
		}
	}
	for (auto& s : sand)
	{
		if (s.first.X > this->MaxX)
		{
			this->MaxX = s.first.X;
		}
		if (s.first.X < this->MinX)
		{
			this->MinX = s.first.X;
		}
		if (s.first.Y > this->MaxY)
		{
			this->MaxY = s.first.Y;
		}
	}
}

void AOC22::Day14::AddRocks(PointMap& rocks, AOC22::Point from, AOC22::Point to)
{
	auto current = from;
	while (true)
	{
		if (current.X != to.X)
		{
			current.X = current.X > to.X ? current.X - 1 : current.X + 1;
		}
		else if (current.Y != to.Y)
		{
			current.Y = current.Y > to.Y ? current.Y - 1 : current.Y + 1;
		}
		else
		{
			break;
		}

		rocks[current] = true;
	}
}

void AOC22::Day14::Display(PointMap& rocks, PointMap& sand, bool animate)
{
	std::string toPrint;

	for (int y = 0; y <= this->MaxY; y++)
	{
		for (int x = this->MinX; x <= this->MaxX; x++)
		{
			if (rocks[AOC22::Point(x, y)])
			{
				toPrint += "#";
			}
			else if (sand[AOC22::Point(x, y)])
			{
				toPrint += "0";
			}
			else if (flow[AOC22::Point(x, y)])
			{
				toPrint += "~";
			}
			else
			{
				toPrint += ".";
			}
		}
		toPrint += "\n";
	}
	if (animate)
	{
		system("CLS");
	}
	printf("%s\n", toPrint.c_str());
}

bool AOC22::Day14::DropSand(PointMap& rocks, PointMap& sand, Point start, int* floor)
{
	Point s(start.X, start.Y);
	this->flow.clear();

	bool outOfBound = false;
	bool running = true;
	//itteration
	for (;running;)
	{
		flow[s] = true;
		Point potentialNewPos(s.X, s.Y + 1);

		if (floor == NULL && potentialNewPos.Y > this->MaxY)
		{
			outOfBound = true;
			running = false;
		}
		else if (floor != NULL && *floor == potentialNewPos.Y)
		{
			sand[s] = true;
			running = false;
			break;
		}

		if (rocks[potentialNewPos] || sand[potentialNewPos])
		{
			potentialNewPos.X -= 1;
			bool canFallLeft = !rocks[potentialNewPos] && !sand[potentialNewPos];

			if (canFallLeft)
			{
				s = potentialNewPos;
				continue;
			}
			else
			{
				potentialNewPos.X += 2;
				bool canFallRight = !rocks[potentialNewPos] && !sand[potentialNewPos];

				if (canFallRight)
				{
					s = potentialNewPos;
					continue;
				}
			}
			sand[s] = true;
			running = false;
			break;
		}

		s = potentialNewPos;
	}

	flow[s] = true;
	return outOfBound;
}

void AOC22::Day14::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	PointMap rocks;
	PointMap sand;

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> results;
		AOCCORE::RegularExpressions::RunIteratorSearch(row, "(\\d+),(\\d+)", results);

		auto x = std::stoi(results[0].substr(0, results[0].find(',')));
		auto y = std::stoi(results[0].substr(results[0].find(',') + 1));

		auto start = AOC22::Point(x, y);
		rocks[start] = true;

		for (size_t i = 1; i < results.size(); i++)
		{
			x = std::stoi(results[i].substr(0, results[i].find(',')));
			y = std::stoi(results[i].substr(results[i].find(',') + 1));

			AddRocks(rocks, start, AOC22::Point(x, y));
			start = AOC22::Point(x, y);
		}
	}

	CalculateMaxSize(rocks, sand);

	int points = 0;
	for (int i = 0; true; i++)
	{
		if (DropSand(rocks, sand, Point(500, 0)))
		{
			points = i;
			break;
		}
	}

	printf("1) (%i)\n", points);
}

void AOC22::Day14::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	PointMap rocks;
	PointMap sand;

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> results;
		AOCCORE::RegularExpressions::RunIteratorSearch(row, "(\\d+),(\\d+)", results);

		auto x = std::stoi(results[0].substr(0, results[0].find(',')));
		auto y = std::stoi(results[0].substr(results[0].find(',') + 1));

		auto start = AOC22::Point(x, y);
		rocks[start] = true;

		for (size_t i = 1; i < results.size(); i++)
		{
			x = std::stoi(results[i].substr(0, results[i].find(',')));
			y = std::stoi(results[i].substr(results[i].find(',') + 1));

			AddRocks(rocks, start, AOC22::Point(x, y));
			start = AOC22::Point(x, y);
		}
	}

	CalculateMaxSize(rocks, sand);

	int points = 0;
	int floor = this->MaxY + 2;
	for (int i = 0; true; i++)
	{
		DropSand(rocks, sand, Point(500, 0), &floor);

		if(sand[Point(500,0)])
		{
			points = i + 1;
			break;
		}
	}

	printf("2) (%i)\n", points);
}

AOC22::Day14::~Day14()
{

}
