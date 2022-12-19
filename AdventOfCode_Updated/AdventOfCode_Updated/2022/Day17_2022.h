#pragma once

#include "../Day.h"
#include "Day14_2022.h"

namespace AOC22
{
	struct TetrisBlock
	{
		std::vector<Point> Blocks;
		int height = 0;

		TetrisBlock(const std::string& blockInfo)
		{
			int x = 0, y = 0;
			for (size_t i = 0; i < blockInfo.size(); i++)
			{
				if (blockInfo[i] == '\n')
				{
					x = 0;
					y--;
				}
				else if (blockInfo[i] == '#')
				{
					Blocks.push_back(Point(x, y));
					x++;
				}
				else
				{
					x++;
				}
			}
			height = std::max(std::abs(y) + 1, 1);
		}

		bool CanMove(const PointMap& map, Point dir) const
		{
			for (Point block : Blocks)
			{
				block.X += dir.X;
				block.Y += dir.Y;

				if (map.find(block) != map.end())
				{
					return false; // cant move because its another block there.
				}

				if (block.X == 0 || block.X == 8) 
				{
					return false;
				}
			}

			return true;
		}
		void Move(Point dir)
		{
			for (Point& block : Blocks)
			{
				block.X += dir.X;
				block.Y += dir.Y;
			}
		}
		size_t LockBlock(PointMap& map)
		{
			size_t highestPoint = 0;
			for (auto& block : Blocks)
			{
				highestPoint = std::max((size_t)block.Y, highestPoint);
				map[block] = true;
			}
			return highestPoint;
		}
		int HighestPoint()
		{
			int highestPoint = 0;
			for (auto& block : Blocks)
			{
				highestPoint = std::max(block.Y, highestPoint);
			}
			return highestPoint;
		}
		bool Contains(const Point& p)
		{
			return std::find(Blocks.begin(), Blocks.end(), p) != Blocks.end();
		}
	};

	struct TetrisSnapshot
	{
		std::vector<std::string> Snapshot;
		size_t Itteration;
		size_t Height;

		TetrisSnapshot(std::vector<std::string> snapshot, size_t itteration, size_t height) : Itteration(itteration), Height(height)
		{
			for (auto& s : snapshot)
			{
				Snapshot.push_back(s);
			}
		}

		inline bool operator==(const TetrisSnapshot& other) const
		{
			for (int i = 0; i < this->Snapshot.size(); i++)
			{
				if (this->Snapshot[i] != other.Snapshot[i])
				{
					return false;
				}
			}
			return true;
		}
	};

	class Day17 : public Day
	{
	private:
		std::vector<TetrisSnapshot> snapshots;
		void PrintMap(const PointMap&, TetrisBlock&, int);
		bool LoopDetector(const PointMap&, size_t, size_t, std::pair<size_t, size_t>&);
	public:
		Day17();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day17();
	};
}
