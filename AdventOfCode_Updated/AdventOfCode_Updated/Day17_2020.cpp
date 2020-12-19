#include "Day17_2020.h"
#include <algorithm>
#include <iostream>

void AOC20::Day17::UpdateLayers()
{
	std::map<Coordinate3D, bool> temp{};

	for (auto cell : _powerGrid3D)
	{
		temp[cell.first] = cell.second;
		Coordinate3D position = cell.first;
		size_t onNeighbors = 0;

		for (int x = -1; x < 2; ++x)
		{
			for (int y = -1; y < 2; ++y)
			{
				for (int z = -1; z < 2; ++z)
				{
					if (x == 0 && y == 0 && z == 0)
					{
						continue;
					}

					Coordinate3D newPos = { position.X + x, position.Y + y, position.Z + z };

					if (_powerGrid3D.find(newPos) == _powerGrid3D.end())
					{
						temp[newPos] = false;
					}
					else if (_powerGrid3D[newPos])
					{
						++onNeighbors;
					}
				}
			}
		}

		if (cell.second && (onNeighbors != 2 && onNeighbors != 3))
		{
			temp[cell.first] = false;
		}
		else if(!cell.second && onNeighbors == 3)
		{
			temp[cell.first] = true;
		}
	}
	_powerGrid3D = temp;
}

void AOC20::Day17::UpdateLayers4D()
{
	std::map<Coordinate4D, bool> temp;

	for (auto cell : _powerGrid4D)
	{
		temp[cell.first] = cell.second;
		Coordinate4D position = cell.first;
		size_t onNeighbors = 0;

		for (int x = -1; x < 2; ++x)
		{
			for (int y = -1; y < 2; ++y)
			{
				for (int z = -1; z < 2; ++z)
				{
					for (int w = -1; w < 2; ++w)
					{
						if (x == 0 && y == 0 && z == 0 && w == 0)
						{
							continue;
						}

						Coordinate4D newPos = { position.X + x, position.Y + y, position.Z + z, position.W + w };

						if (_powerGrid4D.find(newPos) == _powerGrid4D.end())
						{
							temp[newPos] = false;
						}
						else if (_powerGrid4D[newPos])
						{
							++onNeighbors;
						}
					}
				}
			}
		}

		if (cell.second && (onNeighbors != 2 && onNeighbors != 3))
		{
			temp[cell.first] = false;
		}
		else if (!cell.second && onNeighbors == 3)
		{
			temp[cell.first] = true;
		}
	}
	_powerGrid4D = temp;
}

AOC20::Day17::Day17() : Day("2020//Input//day17_data.txt", "2020//Input//day17_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day17::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);
	std::string row;

	_powerGrid3D.clear();

	for (int y = 0; input.NextRow(row); ++y)
	{
		for (int x = 0; x < row.size(); ++x)
		{
			if (row[x] == '#')
			{
				_powerGrid3D[{x, y, 0}] = true;
			}
			else
			{
				_powerGrid3D[{x, y, 0}] = false;
			}
		}
	}

	auto temp = _powerGrid3D;
	for(auto cell : temp)
	{
		auto pos = cell.first;
		for (int x = -1; x < 2; ++x)
		{
			for (int y = -1; y < 2; ++y)
			{
				for (int z = -1; z < 2; ++z)
				{
					Coordinate3D newPos = { pos.X + x, pos.Y + y, pos.Z + z };
					if (_powerGrid3D.find(newPos) == _powerGrid3D.end())
					{
						_powerGrid3D[newPos] = false;
					}
				}
			}
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		UpdateLayers();
	}

	size_t nr = std::count_if(_powerGrid3D.begin(), _powerGrid3D.end(), [](std::pair<Coordinate3D, bool> a) {return a.second; });

	printf("[%s-%s] : Power source cubes active in 3D {%d}.\n", _name.c_str(), __func__, nr);
}

void AOC20::Day17::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);
	_powerGrid4D.clear();

	std::string row;

	for (int y = 0; input.NextRow(row); ++y)
	{
		for (int x = 0; x < row.size(); ++x)
		{
			if (row[x] == '#')
			{
				_powerGrid4D[{x, y, 0, 0}] = true;
			}
			else
			{
				_powerGrid4D[{x, y, 0, 0}] = false;
			}
		}
	}	

	auto temp = _powerGrid4D;
	for (auto cell : temp)
	{
		auto pos = cell.first;
		for (int x = -1; x < 2; ++x)
		{
			for (int y = -1; y < 2; ++y)
			{
				for (int z = -1; z < 2; ++z)
				{
					for (int w = -1; w < 2; ++w)
					{
						Coordinate4D newPos = { pos.X + x, pos.Y + y, pos.Z + z, pos.W + w };
						if (_powerGrid4D.find(newPos) == _powerGrid4D.end())
						{
							_powerGrid4D[newPos] = false;
						}
					}
				}
			}
		}
	}
	
	for (int i = 0; i < 6; ++i)
	{
		UpdateLayers4D();
	}
	

	size_t nr = std::count_if(_powerGrid4D.begin(), _powerGrid4D.end(), [](std::pair<Coordinate4D, bool> a) {return a.second; });

	printf("[%s-%s] : Power source cubes active in 4D {%d}.\n", _name.c_str(), __func__, nr);
}

AOC20::Day17::~Day17()
{
}