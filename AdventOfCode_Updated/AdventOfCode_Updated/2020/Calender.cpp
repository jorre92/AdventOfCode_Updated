#include "Calender.h"

#include "../DayNone.h"
#include "../Day01_2020.h"
#include "../Day02_2020.h"
#include "../Day03_2020.h"
#include "../Day04_2020.h"
#include "../Day05_2020.h"
#include "../Day06_2020.h"
#include "../Day16_2020.h"
#include "../Day17_2020.h"
#include "../Day18_2020.h"
#include "../Day19_2020.h"
#include "../Day20_2020.h"
#include "../Day21_2020.h"
#include "../Day22_2020.h"
#include "../Day23_2020.h"

Day* AOC20::Calander::CreateSolution(AOCCORE::CalenderDay calenderDay) const
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
	case AOCCORE::CalenderDay::Three:
		day = new Day03();
		break;
	case AOCCORE::CalenderDay::Four:
		day = new Day04();
		break;
	case AOCCORE::CalenderDay::Five:
		day = new Day05();
		break;
	case AOCCORE::CalenderDay::Six:
		day = new Day06();
		break;
	case AOCCORE::CalenderDay::Sixteen:
		day = new Day16();
		break;
	case AOCCORE::CalenderDay::Seventeen:
		day = new Day17();
		break;
	case AOCCORE::CalenderDay::Eighteen:
		day = new Day18();
		break;
	case AOCCORE::CalenderDay::Nineteen:
		day = new Day19();
		break;
	case AOCCORE::CalenderDay::Twenty:
		day = new Day20();
		break;
	case AOCCORE::CalenderDay::TwentyOne:
		day = new Day21();
		break;
	case AOCCORE::CalenderDay::TwentyTwo:
		day = new Day22();
		break;
	case AOCCORE::CalenderDay::TwentyThree:
		day = new Day23();
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