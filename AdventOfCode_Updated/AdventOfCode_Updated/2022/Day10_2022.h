#pragma once
#include <iostream>

#include "../Day.h"

namespace AOC22
{
	struct CRTScreen
	{
		int Position = 0;

		void DrawPixel(int centerPos)
		{
			bool sprite = std::abs(Position - centerPos) <= 1;

			std::cout << (sprite ? '#' : '.');
			Position++;

			if (Position == 40)
			{
				std::cout << std::endl;
				Position = 0;
			}
		}
	};

	struct ElfProcessor
	{
		int XValue = 1;
		int Cycle = 1;

		int SignalCommand(const std::string& row)
		{
			int returnValue = 0;

			if (row == "noop")
			{
				Cycle++;
				returnValue += Cycle * XValue * ((Cycle == 20) || ((20 + Cycle) % 40 == 0));
			}
			else
			{
				int toAdd = std::stoi(row.substr(4));

				Cycle++;
				returnValue += Cycle * XValue * ((Cycle == 20) || ((20 + Cycle) % 40 == 0));

				Cycle++;
				XValue += toAdd;
				returnValue += Cycle * XValue * ((Cycle == 20) || ((20 + Cycle) % 40 == 0));
			}

			return returnValue;
		}
		void RenderCommand(CRTScreen& screen, const std::string& row)
		{
			if (row == "noop")
			{
				screen.DrawPixel(XValue);
				Cycle++;
			}
			else
			{
				int toAdd = std::stoi(row.substr(4));
				screen.DrawPixel(XValue);
				Cycle++;

				screen.DrawPixel(XValue);
				Cycle++;
				XValue += toAdd;
			}
		}
	};

	

	class Day10 : public Day
	{
	private:
	public:
		Day10();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day10();
	};
}
