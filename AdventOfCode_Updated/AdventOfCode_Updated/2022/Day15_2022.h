#pragma once

#include "../Day.h"

namespace AOC22
{
	namespace DAY15
	{
		struct Point
		{
			long X = 0;
			long Y = 0;

			Point(long x, long y) : X(x), Y(y) {}

			inline long Manhattan(const Point& other) const { return std::abs(this->X - other.X) + std::abs(this->Y - other.Y); }
			inline void TakeMinValues(const Point& other) 
			{

				this->X = this->X > other.X ? other.X : this->X;
				this->Y = this->Y > other.Y ? other.Y : this->Y;
			}
			inline void TakeMaxValues(const Point& other)
			{

				this->X = this->X < other.X ? other.X : this->X;
				this->Y = this->Y < other.Y ? other.Y : this->Y;
			}

			inline bool operator==(const Point& other) const { return this->X == other.X && this->Y == other.Y; };
			inline bool operator!=(const Point& other) const { return this->X != other.X || this->Y != other.Y; };
		};

		struct Sensor
		{
			Point Position;
			Point ClosestBeacon;
			long SignalRange;

			Sensor(Point p, Point Cb) : Position(p), ClosestBeacon(Cb)
			{
				SignalRange = Position.Manhattan(ClosestBeacon);
			};
		};

		struct Beacon
		{
			Point Position;
			long Range = 0;

			Beacon(Point p) : Position(p) {}

			void NewSignal(const Point& s)
			{
				auto distance = Position.Manhattan(s);

				Range = Range < distance ? distance : Range;
			}

			bool InRange(const Point& s) const { return Position.Manhattan(s) < Range; }
		};
	}
	

	class Day15 : public Day
	{
	private:
		std::vector<DAY15::Sensor> signals;
		bool IsValidBeacon(DAY15::Point&);
		bool CanPlaceBeacon(DAY15::Point&);
		bool CheckAroundSignal(DAY15::Sensor&, long, long, DAY15::Point&);
	public:
		Day15();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day15();
	};
}
