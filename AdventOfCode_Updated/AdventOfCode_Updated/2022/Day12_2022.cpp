#include <iostream>
#include <vector>

#include "../2022/Day12_2022.h"

AOC22::Day12::Day12() : Day("Input//2022//day12_data.txt", "Input//2022//day12_data_simple.txt")
{
}

void AOC22::PathFinder::AddToCheckList(MapCordinate* center, bool dir)
{
	for (int y = center->Y-1; y <= center->Y + 1; ++y)
	{
		if (!(y == -1 || y == this->Map.size())) // is inside the map Y
		{
			for (int x = center->X - 1; x <= center->X + 1; ++x)
			{
				if (!(x == -1 || x == this->Map[y].size())) // is inside the map X
				{
					if ((x == center->X && y != center->Y) || (x != center->X && y == center->Y))
					{
						auto& checkAgainst = this->Map[y][x];
						auto hightCheck = dir ? checkAgainst.Hight - center->Hight <= 1 : center->Hight - checkAgainst.Hight <= 1;
						if ((checkAgainst.Parent == nullptr && hightCheck))
						{
							this->Map[y][x].Parent = center;
							this->CheckList.push_back(&(this->Map[y][x]));
						}
					}
				}
			}
		}
	}
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
	this->worldMap.End->Hight = 'z'+1;
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

	//loop checklist
	while (pf.CheckList.size() > 0)
	{
		auto toCheck = pf.CheckList[0];
		if (toCheck->Hight == 'z' + 1)
		{
			int steps = 0;
			auto step = pf.CheckList[0];
			while (step->Parent != step)
			{
				steps++;
				step = step->Parent;
			}
			printf("1) (%i)\n", steps);
			break;
		}
		pf.AddToCheckList(pf.CheckList[0]);
		pf.CheckList.erase(pf.CheckList.begin());
	}
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

	//loop checklist
	while (pf.CheckList.size() > 0)
	{
		auto toCheck = pf.CheckList[0];
		if (toCheck->Hight == 'a')
		{
			int steps = 0;
			auto step = pf.CheckList[0];
			while (step->Hight != 'z' + 1)
			{
				steps++;
				step = step->Parent;
			}
			printf("2) (%i)\n", steps);
			break;
		}
		pf.AddToCheckList(pf.CheckList[0], false);
		pf.CheckList.erase(pf.CheckList.begin());
	}
}

AOC22::Day12::~Day12()
{

}