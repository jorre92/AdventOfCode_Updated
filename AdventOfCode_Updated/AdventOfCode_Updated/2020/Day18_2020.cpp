#include "Day18_2020.h"

uint64_t AOC20::Day18::NextValue(char** startingPointer, bool partOne)
{
	uint64_t value;

	while (true)
	{
		switch (*(*startingPointer))
		{
		case '(':
			(*startingPointer)++;
			value = Evaluate(startingPointer, partOne);
			(*startingPointer)++;
			return value;
		case ' ':
			(*startingPointer)++;
			break;
		default:
			size_t length = 0;
			value = std::stoull((*startingPointer), &length);
			(*startingPointer) += length;
			return value;
		}
	}

	return value;
}

uint64_t AOC20::Day18::Evaluate(char** stringPointer, bool partOne)
{
	uint64_t value;

	value = NextValue(stringPointer, partOne);

	while (true)
	{
		switch (*(*stringPointer))
		{
		case '\0':
			return value;
		case ')':
			return value;
		case ' ':
			(*stringPointer)++;
			break;
		case '+':
			(*stringPointer)++;
			value += NextValue(stringPointer, partOne);
			break;
		case '*':
			(*stringPointer)++;
			value *= partOne ? NextValue(stringPointer, partOne) : Evaluate(stringPointer, partOne);
			break;
		default:
			return value;
		}
	}

	return uint64_t();
}

AOC20::Day18::Day18() : Day("2020//Input//day18_data.txt", "2020//Input//day18_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day18::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);
	uint64_t sum = 0;

	for (std::string s; input.NextRow(s);)
	{
		char* c = &s[0];
		uint64_t value = Evaluate(&c);
		sum += value;
	}

	printf("[%s-%s] : The sum of all the homework is {%llu}.\n", _name.c_str(), __func__, sum);
}

void AOC20::Day18::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);
	uint64_t sum = 0;

	for (std::string s; input.NextRow(s);)
	{
		char* c = &s[0];
		uint64_t value = Evaluate(&c, false);
		sum += value;
	}

	printf("[%s-%s] : The sum of all the homework is {%llu}.\n", _name.c_str(), __func__, sum);
}

AOC20::Day18::~Day18()
{
}