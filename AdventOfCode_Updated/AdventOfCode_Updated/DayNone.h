#pragma once
#include "Day.h"

class DayNone : public Day
{
public:
	DayNone();

	void SolvePartOne(bool) override;
	void SolvePartTwo(bool) override;
};

