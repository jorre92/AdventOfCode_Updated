#include <algorithm>

#include "../2022/Day15_2022.h"
#include "../RegularExpressions.h"

using namespace AOC22::DAY15;

AOC22::Day15::Day15() : Day("Input//2022//day15_data.txt", "Input//2022//day15_data_simple.txt")
{
}

bool AOC22::Day15::IsValidBeacon(DAY15::Point& point)
{
	bool canItBeHere = true;

	for (auto& s : this->signals)
	{
		long distance = s.Position.Manhattan(point);
		bool IsBeacon = (point == s.ClosestBeacon);

		if (distance <= s.SignalRange || IsBeacon)
		{
			canItBeHere = false;
			break;
		}
	}

	return canItBeHere;
}

bool AOC22::Day15::CanPlaceBeacon(DAY15::Point& point)
{
	bool canItBeHere = true;

	for (auto& s : this->signals)
	{
		long distance = s.Position.Manhattan(point);
		bool IsBeacon = (point == s.ClosestBeacon);

		if (distance <= s.SignalRange && !IsBeacon)
		{
			canItBeHere = false;
			break;
		}
	}

	return canItBeHere;
}

bool AOC22::Day15::CheckAroundSignal(DAY15::Sensor& signal, long minValue, long maxValue, Point& p)
{
	long outsideOfRange = signal.SignalRange + 1;
	for (long checkY = signal.Position.Y - outsideOfRange; checkY <= signal.Position.Y + outsideOfRange; checkY++)
	{
		long distanceFromCenterY = std::abs(checkY - signal.Position.Y);
		long xDif = std::abs(distanceFromCenterY - outsideOfRange);

		if (xDif == 0)
		{
			p = Point(signal.Position.X, signal.Position.Y + (checkY - signal.Position.Y));

			if ((p.X >= 0 && p.X <= maxValue) && (p.Y >= 0 && p.Y <= maxValue) && IsValidBeacon(p))
			{
				return true;
			}
		}
		else
		{
			p = Point(signal.Position.X + xDif, signal.Position.Y + (checkY - signal.Position.Y));

			if ((p.X >= 0 && p.X <= maxValue) && (p.Y >= 0 && p.Y <= maxValue) && IsValidBeacon(p))
			{
				return true;
			}

			p = Point(signal.Position.X - xDif, signal.Position.Y + (checkY - signal.Position.Y));

			if ((p.X >= 0 && p.X <= maxValue) && (p.Y >= 0 && p.Y <= maxValue) && IsValidBeacon(p))
			{
				return true;
			}
		}
	}

	return false;
}


void AOC22::Day15::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	Point minValues(LONG_MAX, LONG_MAX);
	Point maxValues(LONG_MIN, LONG_MIN);

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> results;
		std::string regEx = R"(x=(-?\d+), y=(-?\d+))";

		AOCCORE::RegularExpressions::RunSearch(row.substr(0, row.find(':')), regEx, results);
		Point sensorPos(std::stol(results[1]), std::stol(results[2]));
		AOCCORE::RegularExpressions::RunSearch(row.substr(row.find(':')), regEx, results);
		Point closesBeaconPos(std::stol(results[1]), std::stol(results[2]));

		minValues.TakeMinValues(Point(sensorPos.X - sensorPos.Manhattan(closesBeaconPos), sensorPos.Y - sensorPos.Manhattan(closesBeaconPos)));
		maxValues.TakeMaxValues(Point(sensorPos.X + sensorPos.Manhattan(closesBeaconPos), sensorPos.Y + sensorPos.Manhattan(closesBeaconPos)));

		this->signals.push_back(Sensor(sensorPos, closesBeaconPos));
	}

	long rowY = simple ? 10 : 2000000;
	int points = 0;

	for (long x = minValues.X; x <= maxValues.X; x++)
	{
		Point potentialBeacon(x, rowY);
		bool canItBeHere = true;

		if (!CanPlaceBeacon(potentialBeacon))
		{
			points++;
		}
	}

	printf("1) (%i)\n", points);
}

void AOC22::Day15::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);
	this->signals.clear();

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> results;
		std::string regEx = R"(x=(-?\d+), y=(-?\d+))";

		AOCCORE::RegularExpressions::RunSearch(row.substr(0, row.find(':')), regEx, results);
		Point sensorPos(std::stol(results[1]), std::stol(results[2]));
		AOCCORE::RegularExpressions::RunSearch(row.substr(row.find(':')), regEx, results);
		Point closesBeaconPos(std::stol(results[1]), std::stol(results[2]));

		this->signals.push_back(Sensor(sensorPos, closesBeaconPos));
	}

	long maxValue = simple ? 20 : 4000000;
	size_t answer = 0;
	bool found = false;

	for (auto& signal : this->signals)
	{
		long outsideOfRange = (signal.SignalRange + 1);
		Point found(0,0);
		if (CheckAroundSignal(signal, 0, maxValue, found))
		{
			answer = static_cast<size_t>(found.X) * 4000000 + static_cast<size_t>(found.Y);
			break;
		}
	}
	printf("2) (%llu)\n", answer);
}

AOC22::Day15::~Day15()
{

}
