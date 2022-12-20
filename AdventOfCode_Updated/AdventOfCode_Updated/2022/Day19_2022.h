#pragma once

#include "../Day.h"

namespace AOC22
{
	struct Bluprint
	{
		int Id;
		int OreCostOreRobot;
		int OreCostClayRobot;
		int OreCostObsidianRobot;
		int ClayCostObsidianRobot;
		int OreCostGeodeRobot;
		int ObsidianCostGeodeRobot;

		int HighestCostOre;

		Bluprint(const std::vector<std::string>& costs)
		{
			Id = std::stoi(costs[0]);
			OreCostOreRobot = std::stoi(costs[1]);
			OreCostClayRobot = std::stoi(costs[2]);
			OreCostObsidianRobot = std::stoi(costs[3]);
			ClayCostObsidianRobot = std::stoi(costs[4]);
			OreCostGeodeRobot = std::stoi(costs[5]);
			ObsidianCostGeodeRobot = std::stoi(costs[6]);

			HighestCostOre = std::max(std::max(OreCostOreRobot, OreCostClayRobot), std::max(OreCostObsidianRobot, OreCostGeodeRobot));
		}
	};

	struct ExplorerState
	{
		int TimeLeft = 0;
		int OreRobots = 0;
		int ClayRobots = 0;
		int ObsidianRobots = 0;
		int GeodeRobots = 0;

		int Ore = 0;
		int Clay = 0;
		int Obsidian = 0;
		int Geode = 0;

		struct ExplorerState() : TimeLeft(0), OreRobots(0), ClayRobots(0), ObsidianRobots(0), GeodeRobots(0), Ore(0), Clay(0), Obsidian(0), Geode(0)
		{
		}

		struct ExplorerState(const ExplorerState& ref) : TimeLeft(ref.TimeLeft), OreRobots(ref.OreRobots), ClayRobots(ref.ClayRobots), ObsidianRobots(ref.ObsidianRobots), GeodeRobots(ref.GeodeRobots), Ore(ref.Ore), Clay(ref.Clay), Obsidian(ref.Obsidian), Geode(ref.Geode)
		{
		}

		void operator=(const ExplorerState& other)
		{
			TimeLeft = other.TimeLeft;
			OreRobots = other.OreRobots;
			ClayRobots = other.ClayRobots;
			ObsidianRobots = other.ObsidianRobots;
			GeodeRobots = other.GeodeRobots;

			Ore = other.Ore;
			Clay = other.Clay;
			Obsidian = other.Obsidian;
			Geode = other.Geode;
		}

		bool BuildOreRobot(const Bluprint& b)
		{
			if (b.OreCostOreRobot <= Ore)
			{
				UpdateExplorerState();
				Ore = Ore - b.OreCostOreRobot;
				OreRobots = OreRobots + 1;
				return true;
			}

			return false;
		}

		bool BuildClayRobot(const Bluprint& b)
		{
			if (b.OreCostClayRobot <= Ore)
			{
				UpdateExplorerState();
				Ore = Ore - b.OreCostClayRobot;
				ClayRobots = ClayRobots + 1;
				return true;
			}

			return false;
		}

		bool BuildObsidianRobot(const Bluprint& b)
		{
			if (b.OreCostObsidianRobot <= Ore && b.ClayCostObsidianRobot <= Clay)
			{
				UpdateExplorerState();
				Ore = Ore - b.OreCostObsidianRobot;
				Clay = Clay - b.ClayCostObsidianRobot;
				ObsidianRobots = ObsidianRobots + 1;
				return true;
			}

			return false;
		}

		bool BuildGeodeRobot(const Bluprint& b)
		{
			if (b.OreCostGeodeRobot <= Ore && b.ObsidianCostGeodeRobot <= Obsidian)
			{
				UpdateExplorerState();
				Ore = Ore - b.OreCostGeodeRobot;
				Obsidian = Obsidian - b.ObsidianCostGeodeRobot;
				GeodeRobots = GeodeRobots + 1;
				Geode += TimeLeft;
				return true;
			}

			return false;
		}

		void UpdateExplorerState()
		{
			if (TimeLeft == 0)
			{
				return;
			}

			Ore += OreRobots;
			Clay += ClayRobots;
			Obsidian += ObsidianRobots;
			//Geode += GeodeRobots;
			TimeLeft--;
		}
	};

	class Day19 : public Day
	{
	private:
		void UpdateExplorerState(ExplorerState&) const;
		ExplorerState BFS_TEST(const Bluprint&, ExplorerState);
	public:
		Day19();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day19();
	};
}
