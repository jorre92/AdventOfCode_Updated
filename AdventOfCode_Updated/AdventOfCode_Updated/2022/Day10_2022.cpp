#include <iostream>

#include "../2022/Day10_2022.h"

AOC22::Day10::Day10() : Day("Input//2022//day10_data.txt", "Input//2022//day10_data_simple.txt")
{
}

void AOC22::Day10::SolvePartOne(bool simple)
{
	ElfProcessor processor;
	int signalValue = 0;

	auto input = Day::Input(simple);

	for (std::string row; input.NextRow(row);)
	{
		signalValue += processor.SignalCommand(row);
	}
	std::cout << signalValue << std::endl;
}

void AOC22::Day10::SolvePartTwo(bool simple)
{
	ElfProcessor processor;

	struct CRTScreen screen;

	auto input = Day::Input(simple);

	for (std::string row; input.NextRow(row);)
	{
		processor.RenderCommand(screen, row);
	}
}

AOC22::Day10::~Day10()
{
}