#include "Calender.h"

#include "../DayNone.h"
#include "../2022/Day01_2022.h"
#include "../2022/Day02_2022.h"
#include "../2022/Day03_2022.h"
#include "../2022/Day04_2022.h"
#include "../2022/Day05_2022.h"
#include "../2022/Day06_2022.h"

Day* AOC20::Calander::CreateSolution(AOCCORE::CalenderDay calenderDay) const
{
	Day* day;

	switch (calenderDay)
	{
	case AOCCORE::CalenderDay::One:
		day = new AOC22::Day01();
		break; 
	case AOCCORE::CalenderDay::Two:
		day = new AOC22::Day02();
		break;
	case AOCCORE::CalenderDay::Three:
		day = new AOC22::Day03();
		break;
	case AOCCORE::CalenderDay::Four:
		day = new AOC22::Day04();
		break;
	case AOCCORE::CalenderDay::Five:
		day = new AOC22::Day05();
		break;
	case AOCCORE::CalenderDay::Six:
		day = new AOC22::Day06();
		break;
	default:
		day = new DayNone();
		break;
	}

	return day;
}

void AOC20::Calander::DestroySolution(Day* solution) const
{
	delete(solution);
}