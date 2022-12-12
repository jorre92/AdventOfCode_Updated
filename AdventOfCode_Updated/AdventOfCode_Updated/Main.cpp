
#include <iostream>
#include <chrono>

#include "Day.h"
#include "2020/Calender.h"

namespace EXECUTE
{
	void Exe(AOCCORE::CalenderDay dayId, bool simpleData = false)
	{
		Day* day;
		AOC20::Calander calender;

		day = calender.CreateSolution(dayId);

		printf("---- Day %d ----\n", ((int)dayId) + 1);
		auto startPartOne = std::chrono::high_resolution_clock::now();
		day->SolvePartOne(simpleData);
		auto endPartOne = std::chrono::high_resolution_clock::now();

		auto startPartTwo = std::chrono::high_resolution_clock::now();
		day->SolvePartTwo(simpleData);
		auto endPartTwo = std::chrono::high_resolution_clock::now();

		auto durationPartOne = std::chrono::duration_cast<std::chrono::milliseconds>(endPartOne - startPartOne);
		auto durationPartTwo = std::chrono::duration_cast<std::chrono::milliseconds>(endPartTwo - startPartTwo);

		printf("Solution time part one/two: %llu/%llu (ms)\n", durationPartOne.count(), durationPartTwo.count());

		calender.DestroySolution(day);
	}
}

#define DEBUG

int main()
{

#ifdef DEBUG
	EXECUTE::Exe(AOCCORE::CalenderDay::Eleven, false);
#endif // DEBUG


#ifndef DEBUG
	for (int i = 0; i < AOCCORE::CalenderDay::NumberOfDays; ++i)
	{
		EXECUTE::Exe((AOCCORE::CalenderDay)i, true);
	}
#endif // !DEBUG

	return EXIT_SUCCESS;
}