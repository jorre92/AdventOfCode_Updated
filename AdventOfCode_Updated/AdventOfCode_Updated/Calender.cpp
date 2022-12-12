#include "Calender.h"
#include "CalenderDay.h"
#include "Day.h"
#include "DayNone.h"

Day* AOCCORE::Calander::CreateSolution(AOCCORE::CalenderDay calenderDay) const
{
	Day* day;

	switch (calenderDay)
	{
	default:
		day = new DayNone();
		break;
	}

	return day;
}

void AOCCORE::Calander::DestroySolution(Day* solution) const
{
	delete(solution);
}