#include <iostream>
#include <vector>

#include "../2022/Day12_2022.h"

AOC22::Day12::Day12() : Day("Input//2022//day12_data.txt", "Input//2022//day12_data_simple.txt")
{
}

void AOC22::PathFinder::AddToCheckList(MapCordinate* center, bool goingUp)
{
	for (int y = center->Y-1; y <= center->Y + 1; ++y)
	{
		if ((y == -1 || y == this->Map.size()))
		{
			continue;
		}

		for (int x = center->X - 1; x <= center->X + 1; ++x)
		{
			if (!((x == center->X && y != center->Y) || (x != center->X && y == center->Y)) || (x == -1 || x >= this->Map[y].size()))
			{
				continue;
			}

			auto accessible = goingUp ? 
				this->Map[y][x].Hight - center->Hight <= 1 :
				center->Hight - this->Map[y][x].Hight <= 1;
			auto isUncharted = this->Map[y][x].Parent == nullptr;

			if (accessible && isUncharted)
			{
				this->Map[y][x].Parent = center;
				this->CheckList.push_back(&(this->Map[y][x]));
			}
		}
	}
}

std::vector<AOC22::MapCordinate> AOC22::PathFinder::FindPath(int goalX, int goalY, bool goingUp)
{
	std::vector<AOC22::MapCordinate> path;

	while (this->CheckList.size() > 0)
	{
		auto toCheck = this->CheckList[0];
		if (toCheck->X == goalX && toCheck-> Y == goalY)
		{
			int steps = 0;
			while (toCheck->Parent != toCheck)
			{
				path.push_back(*toCheck);
				toCheck = toCheck->Parent;
			}
			break;
		}
		this->AddToCheckList(this->CheckList[0], goingUp);
		this->CheckList.erase(this->CheckList.begin());
	}

	return path;
}

std::vector<AOC22::MapCordinate> AOC22::PathFinder::FindPath(char goalHeight, bool goingUp)
{
	std::vector<AOC22::MapCordinate> path;

	while (this->CheckList.size() > 0)
	{
		auto toCheck = this->CheckList[0];
		if (toCheck->Hight == goalHeight)
		{
			int steps = 0;
			while (toCheck->Parent != toCheck)
			{
				path.push_back(*toCheck);
				toCheck = toCheck->Parent;
			}
			break;
		}
		this->AddToCheckList(this->CheckList[0], goingUp);
		this->CheckList.erase(this->CheckList.begin());
	}

	return path;
}

void AOC22::Day12::ConstructMap(const std::vector<std::string>& mapData)
{
	int xStart = 0, yStart = 0;
	int xEnd = 0, yEnd = 0;
	this->worldMap.map.clear();

	for (int y = 0; y < mapData.size(); ++y)
	{
		this->worldMap.map.push_back(std::vector<MapCordinate>());
		for (int x = 0; x < mapData[0].size(); ++x)
		{
			AOC22::MapCordinate coord;
			coord.Hight = mapData[y][x];
			coord.X = x;
			coord.Y = y;
			coord.Parent = nullptr;
			this->worldMap.map.back().push_back(coord);
			if (coord.Hight == 'S')
			{
				xStart = x;
				yStart = y;
			}
			else if (coord.Hight == 'E')
			{
				xEnd = x;
				yEnd = y;
			}
		}
	}

	this->worldMap.Start = &(this->worldMap.map[yStart][xStart]);
	this->worldMap.End = &(this->worldMap.map[yEnd][xEnd]);

	this->worldMap.Start->Hight = 'a';
	this->worldMap.End->Hight = 'z';
}

void AOC22::Day12::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	for (std::vector<std::string> mapData;input.NextBatch(mapData);)
	{
		ConstructMap(mapData);
	}

	AOC22::PathFinder pf;
	pf.Map = this->worldMap.map;
	pf.Map[this->worldMap.Start->Y][this->worldMap.Start->X].Parent = &(pf.Map[this->worldMap.Start->Y][this->worldMap.Start->X]);
	pf.CheckList.push_back(&(pf.Map[this->worldMap.Start->Y][this->worldMap.Start->X]));

	auto path = pf.FindPath(this->worldMap.End->X, this->worldMap.End->Y);

	printf("1) (%llu)\n", path.size());
}

void AOC22::Day12::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	for (std::vector<std::string> mapData; input.NextBatch(mapData);)
	{
		ConstructMap(mapData);
	}

	AOC22::PathFinder pf;
	pf.Map = this->worldMap.map;
	pf.Map[this->worldMap.End->Y][this->worldMap.End->X].Parent = &(pf.Map[this->worldMap.End->Y][this->worldMap.End->X]);
	pf.CheckList.push_back(&(pf.Map[this->worldMap.End->Y][this->worldMap.End->X]));

	auto path = pf.FindPath('a');

	printf("2) (%llu)\n", path.size());
}

AOC22::Day12::~Day12()
{

}