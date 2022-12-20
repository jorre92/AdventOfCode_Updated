#include "../2022/Day19_2022.h"
#include "../RegularExpressions.h"


void AOC22::Day19::UpdateExplorerState(ExplorerState& state) const
{
	if (state.TimeLeft == 0)
	{
		return;
	}

	state.Ore += state.OreRobots;
	state.Clay += state.ClayRobots;
	state.Obsidian += state.ObsidianRobots;
	state.Geode += state.GeodeRobots;
	state.TimeLeft--;
}


AOC22::ExplorerState AOC22::Day19::BFS_TEST(const AOC22::Bluprint& blueprint, AOC22::ExplorerState state)
{
	if (state.TimeLeft == 0)
	{
		return state;
	}

	AOC22::ExplorerState bestResult(state);

	AOC22::ExplorerState tempState(state);
	while (tempState.TimeLeft >= 1 && tempState.ObsidianRobots >= 1)
	{
		if (tempState.BuildGeodeRobot(blueprint))
		{
			bestResult = BFS_TEST(blueprint, tempState);
			break;
		}
		tempState.UpdateExplorerState();
		if (tempState.TimeLeft == 0)
		{
			bestResult = bestResult.Geode > tempState.Geode ? bestResult : tempState;
			break;
		}
	}
	
	if (blueprint.HighestCostOre > tempState.OreRobots)
	{
		tempState = AOC22::ExplorerState(state);
		while (tempState.TimeLeft >= 1)
		{
			if (tempState.BuildOreRobot(blueprint))
			{
				auto result = BFS_TEST(blueprint, tempState);
				bestResult = bestResult.Geode > result.Geode ? bestResult : result;
				break;
			}
			tempState.UpdateExplorerState();
			if (tempState.TimeLeft == 0)
			{
				bestResult = bestResult.Geode > tempState.Geode ? bestResult : tempState;
				break;
			}
		}
	}

	if (blueprint.ClayCostObsidianRobot > tempState.ClayRobots)
	{
		tempState = AOC22::ExplorerState(state);
		while (tempState.TimeLeft >= 1)
		{
			if (tempState.BuildClayRobot(blueprint))
			{
				auto result = BFS_TEST(blueprint, tempState);
				bestResult = bestResult.Geode > result.Geode ? bestResult : result;
				break;
			}
			tempState.UpdateExplorerState();
			if (tempState.TimeLeft == 0)
			{
				bestResult = bestResult.Geode > tempState.Geode ? bestResult : tempState;
				break;
			}
		}
	}

	if (blueprint.ObsidianCostGeodeRobot > tempState.ObsidianRobots)
	{
		tempState = AOC22::ExplorerState(state);
		while (tempState.TimeLeft >= 1)
		{
			if (tempState.BuildObsidianRobot(blueprint))
			{
				auto result = BFS_TEST(blueprint, tempState);
				bestResult = bestResult.Geode > result.Geode ? bestResult : result;
				break;
			}
			tempState.UpdateExplorerState();
			if (tempState.TimeLeft == 0)
			{
				bestResult = bestResult.Geode > tempState.Geode ? bestResult : tempState;
				break;
			}
		}
	}

	return bestResult;
}

AOC22::Day19::Day19() : Day("Input//2022//day19_data.txt", "Input//2022//day19_data_simple.txt")
{
}

void AOC22::Day19::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	int value = 0; 

	for (std::string row; input.NextRow(row);)
	{
		std::string regex = "([0-9]+)";
		std::vector<std::string> results;
		AOCCORE::RegularExpressions::RunIteratorSearch(row, regex, results);

		AOC22::Bluprint blueprint(results);
		AOC22::ExplorerState initState;

		initState.OreRobots = 1;
		initState.TimeLeft = 24;

		auto result = BFS_TEST(blueprint, initState);
		value += blueprint.Id * result.Geode;
	}
	
	printf("1) (%i)\n", value);
}

void AOC22::Day19::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	int value = 1;
	int i = 0;

	for (std::string row; input.NextRow(row) && i < 3 ; i ++)
	{
		std::string regex = "([0-9]+)";
		std::vector<std::string> results;
		AOCCORE::RegularExpressions::RunIteratorSearch(row, regex, results);

		AOC22::Bluprint blueprint(results);
		AOC22::ExplorerState initState;

		initState.OreRobots = 1;
		initState.TimeLeft = 32;
		
		auto result = BFS_TEST(blueprint, initState);
		value *= result.Geode;
	}
	printf("2) (%i)\n", value);
}

AOC22::Day19::~Day19()
{

}
