#include "Calender.h"

#include "DayNone.h"
#include "2022/Day01_2022.h"
#include "2022/Day02_2022.h"
#include "2022/Day03_2022.h"
#include "2022/Day04_2022.h"
#include "2022/Day05_2022.h"
#include "2022/Day06_2022.h"
#include "2022/Day07_2022.h"
#include "2022/Day08_2022.h"
#include "2022/Day09_2022.h"
#include "2022/Day10_2022.h"
#include "2022/Day11_2022.h"
#include "2022/Day12_2022.h"
#include "2022/Day13_2022.h"
#include "2022/Day14_2022.h"

Day* AOCCORE::Calander::CreateSolution(AOCCORE::CalenderDay calenderDay) const
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
	case AOCCORE::CalenderDay::Seven:
		day = new AOC22::Day07();
		break;
	case AOCCORE::CalenderDay::Eight:
		day = new AOC22::Day08();
		break;
	case AOCCORE::CalenderDay::Nine:
		day = new AOC22::Day09();
		break;
	case AOCCORE::CalenderDay::Ten:
		day = new AOC22::Day10();
		break;
	case AOCCORE::CalenderDay::Eleven:
		day = new AOC22::Day11();
		break;
	case AOCCORE::CalenderDay::Twelve:
		day = new AOC22::Day12();
		break;
	case AOCCORE::CalenderDay::Thirteen:
		day = new AOC22::Day13();
		break; 
	case AOCCORE::CalenderDay::Fourteen:
		day = new AOC22::Day14();
		break;
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