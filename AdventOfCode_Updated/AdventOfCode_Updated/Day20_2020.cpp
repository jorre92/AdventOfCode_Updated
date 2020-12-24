#include "Day20_2020.h"
#include "CameraView.h"
#include <math.h>
#include <algorithm>
#include <map>
#include <iostream>

CameraView& AOC20::Day20::GetCameraByID(size_t id)
{
	return (*std::find(_cameraViews.begin(), _cameraViews.end(), id));
}

AOC20::Day20::Day20() : Day("2020//Input//day20_data.txt", "2020//Input//day20_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day20::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);

	for (std::vector<std::string> mapData; input.NextBatch(mapData);)
	{
		size_t index = std::stoul(mapData[0].substr(5, (mapData[0].length() - 6)));
		mapData.erase(mapData.begin());

		_cameraViews.push_back(CameraView(index, mapData));
	}

	for (int i = 0; i < _cameraViews.size(); i++)
	{
		for (int j = 0; j < _cameraViews.size(); j++)
		{
			if (j == i)
			{
				continue;
			}

			_cameraViews[i].HavePotentialConnection(_cameraViews[j]);
		}
	}
		
	uint64_t product = 1;

	for (auto camera : _cameraViews)
	{
		if (camera.PotentialConnections.size() == 2)
		{
			product *= camera.ID();
		}
	}

	printf("[%s-%s] : The prouct of the corner camera ids {%llu}.\n", _name.c_str(), __func__, product);
}

void AOC20::Day20::SolvePartTwo(bool simpleData)
{
	/*
	auto input = Day::Input(simpleData);
	std::map<size_t, Camera> cameras;

	for (std::vector<std::string> mapData; input.NextBatch(mapData);)
	{
		size_t index = std::stoul(mapData[0].substr(5, (mapData[0].length() - 6)));
		mapData.erase(mapData.begin());

		cameras[index] = Camera(mapData, index);
	}

	for (auto it = cameras.begin(); it != cameras.end(); ++it)
	{
		for (auto _it = cameras.begin(); _it != cameras.end(); ++_it)
		{
			if (it == _it)
			{
				continue;
			}

			(*it).second.ValidConnection(&(*_it).second);
		}

	}

	size_t index = 0;
	for (auto it = cameras.begin(); it != cameras.end(); ++it)
	{

		if ((*it).second.PotentialConnections.size() == 2)
		{
			index = (*it).first;
			break;
		}
	}
	index = 1951;
	std::vector<Camera*> done;
	std::vector<Camera*> WorkingOn { &cameras[index] };

	while (!WorkingOn.empty())
	{
		auto currentWork = WorkingOn.front();
		WorkingOn.erase(WorkingOn.begin());

		auto moreWork = currentWork->PotentialConnections;

		for (auto work : moreWork)
		{
			WorkingOn.push_back(work);
		}

		currentWork->Connect(currentWork->ID == index);
		done.push_back(currentWork);
	}
	*/
	printf("[%s-%s] : .\n", _name.c_str(), __func__);
}

AOC20::Day20::~Day20()
{
}