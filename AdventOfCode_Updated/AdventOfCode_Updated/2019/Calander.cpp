#include "Calander.h"

#include "../DayNone.h"
#include "Day01.h"
#include "Day02.h"

Day* AOC19::Calander::CreateSolution(AOCCORE::CalenderDay calenderDay) const
{
	Day* day;

	switch (calenderDay)
	{
	case AOCCORE::CalenderDay::One:
		day = new Day01();
		break;
	case AOCCORE::CalenderDay::Two:
		day = new Day02();
		break;
	default:
		day = new DayNone();
		break;
	}

	return day;
}

void AOC19::Calander::DestroySolution(Day* solution) const
{
	delete(solution);
}
