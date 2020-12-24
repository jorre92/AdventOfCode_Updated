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

		printf("---- Day %d ----\n", ((size_t)dayId) + 1);
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
	EXECUTE::Exe(AOCCORE::CalenderDay::TwentyThree, false);
#endif // DEBUG


#ifndef DEBUG
	for (int i = 0; i < AOCCORE::CalenderDay::NumberOfDays; ++i)
	{
		EXECUTE::Exe((AOCCORE::CalenderDay)i, true);
	}
#endif // !DEBUG

	return EXIT_SUCCESS;
}

/*
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print(std::vector<int>& cups, int current)
{
    int at = current;
    do {
        std::cout << at;
        at = cups[at];
    } while (at != current);
    std::cout << std::endl;
}

int move(std::vector<int>& cups, int current)
{
    int first = cups[current];
    int last = cups[cups[first]];
    cups[current] = cups[last];

    int destination = current - 1 ? current - 1 : cups.size() - 1;
    bool inremoved = true;
    while (inremoved) {
        int at = first;
        inremoved = false;

        for (int i = 0; i < 3; ++i) {
            if (destination == at) {
                inremoved = true;
                destination = destination - 1 ? destination - 1 : cups.size() - 1;
            }
            at = cups[at];
        }
    }

    cups[last] = cups[destination];
    cups[destination] = first;

    return cups[current];
}

int main()
{
    std::fstream file("2020//Input//day23_data.txt");
    std::string line;
    std::getline(file, line);

    std::vector<int> input(line.size() + 1);
    int previous = line[0] - '0';
    int current = previous;
    int first = current;
    for (int i = 1; i < line.size(); ++i) {
        input[previous] = line[i] - '0';
        previous = input[previous];
    }
    input[previous] = current;

    std::vector<int> cups1(input);
    for (int i = 0; i < 100; ++i) {
        current = move(cups1, current);
    }
    std::cout << "1: ";
    print(cups1, cups1[1]);

    std::vector<int> cups2(input);;
    cups2.resize(1000001);
    current = first;
    for (int i = line.size() + 1; i <= 1000000; ++i) {
        cups2[previous] = i;
        previous = i;
    }
    cups2[previous] = current;

    for (int i = 0; i < 10000000; ++i) {
        current = move(cups2, current);
    }
    std::cout << "2: " << (size_t)cups2[1] * cups2[cups2[1]] << std::endl;

    return 0;
}
*/