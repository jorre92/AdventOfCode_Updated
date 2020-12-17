#include "Day01.h"

int AOC19::Day01::FuleNeeded(int weight)
{
	auto fule = (weight / 3) - 2;

	return fule > 0 ? fule : 0;
}

AOC19::Day01::Day01() : Day("2019//Input//Day01_data.txt", "2019//Input//Day01_data_simple.txt")
{
	//printf("Construction of %s object.\n", __func__);
}

void AOC19::Day01::SolvePartOne(bool simpleData)
{
	auto stream = Day::Input(simpleData);
	auto totalMass = 0;
	auto fuleForAllModules = 0;

	for (auto moduleMass = 0; stream.Next(moduleMass);)
	{
		fuleForAllModules += FuleNeeded(moduleMass);
	}

	printf("[%s] : Total fule needed for all modules:{%d}.\n", __func__, fuleForAllModules);
}

void AOC19::Day01::SolvePartTwo(bool simpleData)
{
	auto stream = Day::Input(simpleData);

	auto fuleNeededForAllModules = 0;

	for (auto moduleMass = 0; stream.Next(moduleMass);)
	{
		auto needsFule = moduleMass;
		auto totalModuleFule = 0;
		auto newFule = FuleNeeded(needsFule);

		do
		{
			needsFule = newFule;
			totalModuleFule += newFule;
			newFule = FuleNeeded(needsFule);
		} while (newFule != 0);

		fuleNeededForAllModules += totalModuleFule;
	}

	printf("[%s] : Total fule needed for all modules:{%d}.\n", __func__, fuleNeededForAllModules);
}

AOC19::Day01::~Day01()
{
	//printf("Destruction of %s object.\n", __func__);
}
