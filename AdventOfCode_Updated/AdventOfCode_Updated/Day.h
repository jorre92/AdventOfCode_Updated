#pragma once
#include "InputExtractor.h"

#include <string>
#include <istream>
class Day
{
private:
	std::string _data;
	std::string _simpleData;
protected:
	std::string _name;
	InputExtractor Input(bool simple = false);
public:
	Day(std::string, std::string);

	virtual void SolvePartOne(bool = false) = 0;
	virtual void SolvePartTwo(bool = false) = 0;

	virtual ~Day();
};

