#pragma once
#include <unordered_set>

#include "../Day.h"

namespace AOC22
{
	template <typename T>
	void hash_combine(std::size_t& seed, const T& val) 
	{
		seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	struct Position
	{
		int X = 0;
		int Y = 0;

		void Move(const struct Position dir)
		{
			X += dir.X;
			Y += dir.Y;
		}

		bool operator==(struct Position const& rhs) const
		{
			return this->X == rhs.X && this->Y == rhs.Y;
		}

		bool operator!=(struct Position const& rhs) const
		{
			return !(*this == rhs);
		}

		Position NextStep(struct Position position)
		{
			int xDif = position.X - X;
			int yDif = position.Y - Y;
			int xDist = std::max(std::abs(xDif), 1);
			int yDist = std::max(std::abs(yDif), 1);

			if (xDist >= 2 || yDist >= 2) 
			{
				Position pos;
				pos.X = X + xDif / xDist;
				pos.Y = Y + yDif / yDist;
				return pos;
			}

			return *this;
		}
	};
	
	struct Position_hash {
		size_t operator()(const Position& p) const {
			std::size_t hash = 0;
			hash_combine(hash, p.X);
			hash_combine(hash, p.Y);
			return hash;
		}
	};

	struct Head
	{
		struct Position position;

		void Move(struct Position& dir)
		{
			position.Move(dir);
		}
	};

	struct Tail
	{
		struct Position position;
		std::unordered_set<struct Position, struct Position_hash> history;

		struct Tail(struct Position pos)
		{
			position = pos;
			history.insert(pos);

		};

		void MoveTo(struct Position to)
		{
			if (position != to)
			{
				position = to;
				history.insert(to);
			}
			
		}
	};

	struct Snake
	{
		Head head;
		std::vector<Tail> body;

		Snake(int bodySize) : head()
		{
			for (int i = 0; i < bodySize; ++i)
			{
				body.push_back(Tail(head.position));
			}
		}

		void Move(struct Position& dir)
		{
			head.Move(dir);

			body[0].MoveTo(body[0].position.NextStep(head.position));

			for (int i = 1; i < body.size(); ++i)
			{
				body[i].MoveTo(body[i].position.NextStep(body[i-1].position));
			}
		}
	};

	class Day09 : public Day
	{
	private:
	public:
		Day09();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day09();
	};
}
