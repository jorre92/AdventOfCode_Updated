#pragma once
#include "Day.h"

namespace AOC20
{
	class Node
	{
	public:
		Node* next;
		Node* previous;
		int Value;
	};

	class Day23 : public Day
	{
	private: 
		int move(std::vector<int>&, int);
	public:
		Day23();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day23();
	};
}