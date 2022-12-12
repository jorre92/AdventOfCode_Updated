#pragma once

#include "../Day.h"

namespace AOC22
{
	struct MapCordinate
	{
		MapCordinate* Parent = this;
		int X, Y;
		char Hight;
	};

	struct Map
	{
		std::vector<std::vector<MapCordinate>> map;
		MapCordinate* Start;
		MapCordinate* End;
	};

	struct PathFinder
	{
		std::vector<std::vector<MapCordinate>> Map;
		std::vector<MapCordinate*> CheckList;
		std::vector<MapCordinate> OpenList;

		void AddToCheckList(MapCordinate*, bool = true);
	};

	class Day12 : public Day
	{
	private:
		Map worldMap;
		void ConstructMap(const std::vector<std::string>& mapData);
	public:
		Day12();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day12();
	};
}
