#pragma once
#include <unordered_map>

#include "../Day.h"

namespace AOC22
{
	class Point {
	public:
		Point(int x, int y) : X(x), Y(y)
		{
		};

		int X, Y;
	};

	struct hashFunc 
	{
		size_t operator()(const Point& k) const
		{
			size_t h1 = std::hash<int>()(k.X);
			size_t h2 = std::hash<int>()(k.Y);
			return h1 ^ (h2 << 1);
		}
	};

	struct equalsFunc 
	{
		bool operator()(const Point& lhs, const Point& rhs) const
		{
			return (lhs.X == rhs.X) && (lhs.Y == rhs.Y);
		}
	};

	typedef std::unordered_map<Point, bool, hashFunc, equalsFunc> PointMap;

	class Day14 : public Day
	{
	private:
		PointMap flow;
		int MaxY = 0;
		int MaxX = 0;
		int MinX = 500;
		void CalculateMaxSize(PointMap&, PointMap&);
		void AddRocks(PointMap&, Point, Point);
		void Display(PointMap&, PointMap&, bool = false);
		bool DropSand(PointMap&, PointMap&, Point, int* = NULL);
	public:
		Day14();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day14();
	};
}
