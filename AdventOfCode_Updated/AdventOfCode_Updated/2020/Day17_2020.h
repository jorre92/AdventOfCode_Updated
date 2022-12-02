#pragma once
#include "../Day.h"
#include <map>

namespace AOC20
{
	struct Coordinate3D
	{
	public:
		int X, Y, Z;
		Coordinate3D(int x, int y, int z) : X(x), Y(y), Z(z) {}
		bool operator== (const Coordinate3D& other) const { return this->X == other.X && this->Y == other.Y && this->Z == other.Z; }
		bool operator< (const Coordinate3D& other) const
		{
			if (X != other.X)
				return (X < other.X);

			if (Y != other.Y)
				return (Y < other.Y);

			return (Z < other.Z);
		}
	};	
	
	struct Coordinate4D
	{
	public:
		int X, Y, Z, W;
		Coordinate4D(int x, int y, int z, int w) : X(x), Y(y), Z(z), W(w) {}
		bool operator== (const Coordinate4D& other) const { return this->X == other.X && this->Y == other.Y && this->Z == other.Z && this->W == other.W; }
		bool operator< (const Coordinate4D& other) const
		{
			if (X != other.X)
				return (X < other.X);

			if (Y != other.Y)
				return (Y < other.Y); 
			
			if (Z != other.Z)
				return (Z < other.Z);

			return (W < other.W);
		}
	};

	class Day17 : public Day
	{
	private:
		std::map<Coordinate3D, bool> _powerGrid3D;
		std::map<Coordinate4D, bool> _powerGrid4D;

		void UpdateLayers();
		void UpdateLayers4D();
	public:
		Day17();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day17();
	};
}