#include <iostream>

#include "../2022/Day05_2022.h"
#include "../RegularExpressions.h"

AOC22::Day05::Day05() : Day("Input//2022//day05_data.txt", "Input//2022//day05_data_simple.txt")
{
	
}

void AOC22::Day05::setUpCargo(std::vector<std::string>& list)
{
	std::reverse(list.begin(), list.end());

	auto size = list[0][list[0].size() - 2] - '0';
	cargoArea.CreatePiles(size);

	for (int i = 1; i < list.size(); i++)
	{
		for (int cargo = 0; cargo < cargoArea.cargoPiles.size(); cargo++)
		{
			auto index = cargo * 4 + 1;
			if (list[i][index] != ' ')
			{
				cargoArea.Add(cargo, list[i][index]);
			}
		}
	}
}

void AOC22::Day05::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<std::string> cargoTemplate;
	input.NextBatch(cargoTemplate);
	setUpCargo(cargoTemplate);

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> instructions;
		AOCCORE::RegularExpressions::RunIteratorSearch(row, "([0-9]+)", instructions);

		cargoArea.Move(std::stoi(instructions[0]), std::stoi(instructions[1]) - 1, std::stoi(instructions[2]) - 1);
	}

	printf("1) (%s)\n", cargoArea.ToString().c_str());
}


void AOC22::Day05::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<std::string> cargoTemplate;
	input.NextBatch(cargoTemplate);

	setUpCargo(cargoTemplate);

	for (std::string row; input.NextRow(row);)
	{
		std::vector<std::string> instructions;
		AOCCORE::RegularExpressions::RunIteratorSearch(row, "([0-9]+)", instructions);

		cargoArea.AdvancedMove(std::stoi(instructions[0]), std::stoi(instructions[1]) - 1, std::stoi(instructions[2]) - 1);
	}

	printf("2) (%s)\n", cargoArea.ToString().c_str());
}

AOC22::Day05::~Day05()
{
}

void AOC22DAY05::cargoArea::CreatePiles(int numberOfPiles)
{
	cargoPiles.clear();

	for (size_t i = 0; i < numberOfPiles; ++i)
	{
		cargoPiles.push_back(std::vector<char>());
	}
}

void AOC22DAY05::cargoArea::Move(int numberOfMoves, int fromPile, int toPile)
{
	for (size_t i = 0; i < numberOfMoves; ++i)
	{
		if (cargoPiles[fromPile].empty())
		{
			break;
		}

		cargoPiles[toPile].push_back(cargoPiles[fromPile].back());

		cargoPiles[fromPile].pop_back();
	}
}

void AOC22DAY05::cargoArea::AdvancedMove(int numberOfMoves, int fromPile, int toPile)
{
	if (cargoPiles[fromPile].size() >= numberOfMoves)
	{
		cargoPiles[toPile].insert(
			cargoPiles[toPile].end(),
			std::make_move_iterator(cargoPiles[fromPile].end() - numberOfMoves),
			std::make_move_iterator(cargoPiles[fromPile].end()));

		cargoPiles[fromPile].erase(cargoPiles[fromPile].end() - numberOfMoves, cargoPiles[fromPile].end());
	}
}

void AOC22DAY05::cargoArea::Add(int pile, char cargo)
{
	this->cargoPiles[pile].push_back(cargo);
}

std::string AOC22DAY05::cargoArea::ToString()
{
	std::string returnValue = "";
	for (auto& pile : cargoPiles)
	{
		if (!pile.empty())
		{
			returnValue += pile.back();
		}
		else
		{
			returnValue += " ";
		}
	}

	return returnValue;
}