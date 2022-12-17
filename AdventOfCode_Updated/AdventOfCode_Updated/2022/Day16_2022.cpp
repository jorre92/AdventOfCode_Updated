#include <algorithm>

#include "../2022/Day16_2022.h"
#include "../RegularExpressions.h"

using namespace AOC22::DAY16;

size_t AOC22::Day16::SimpleFastestPath(std::vector<std::string>Visited, std::string current, std::string to)
{
	if (current == to)
	{
		return Visited.size();
	}
	else
	{
		Visited.push_back(current);

		size_t quickest = 100000;

		for (auto& nValve : this->valves[current].CanAccessTunnels)
		{
			if (std::find(Visited.begin(), Visited.end(), nValve) == Visited.end())
			{
				size_t quick = SimpleFastestPath(Visited, nValve, to);

				if (quick < quickest)
				{
					quickest = quick;
				}
			}
		}

		return quickest;
	}
}

size_t AOC22::Day16::SimpleBestRelease(std::vector<std::string>Visited, std::string current, int timeLeft, size_t released)
{
	if (Visited.size() == this->importantValves.size() || timeLeft <= 0)
	{
		return released;
	}
	else
	{
		if (this->importantValves[current].FlowRate > 0)
		{
			timeLeft -= 1;
			released += timeLeft * this->importantValves[current].FlowRate;
		}
		Visited.push_back(current);

		size_t bestPath = released;
		for (auto& valve : this->importantValves)
		{
			if (std::find(Visited.begin(), Visited.end(), valve.first) == Visited.end())
			{
				auto best = SimpleBestRelease(Visited, valve.first, timeLeft - this->ranges[current + valve.first], released);

				if (best > bestPath)
				{
					bestPath = best;
				}
			}
		}
		return bestPath;
	}
}

size_t AOC22::Day16::SimpleBestReleaseWithElephant(std::vector<std::string>Visited, WorkItem me, WorkItem elephant, int timeLeft, size_t released)
{
	while (timeLeft > 0)
	{
		if (me.TillDone == 0)
		{
			if (std::find(Visited.begin(), Visited.end(), me.WorkingOnValve) == Visited.end())
			{
				if (this->importantValves[me.WorkingOnValve].FlowRate > 0)
				{
					released += timeLeft * this->importantValves[me.WorkingOnValve].FlowRate;
				}
				Visited.push_back(me.WorkingOnValve);

				size_t bestPath = released;
				for (auto& valve : this->importantValves)
				{
					if (std::find(Visited.begin(), Visited.end(), valve.first) == Visited.end())
					{
						auto best = SimpleBestReleaseWithElephant(Visited, WorkItem(this->ranges[me.WorkingOnValve + valve.first] + 1, valve.first), elephant, timeLeft, released);

						if (best > bestPath)
						{
							bestPath = best;
						}
					}
				}
				return bestPath;
			}
			else
			{
				size_t bestPath = released;
				for (auto& valve : this->importantValves)
				{
					if(std::find(Visited.begin(), Visited.end(), valve.first) == Visited.end())
					{
						auto best = SimpleBestReleaseWithElephant(Visited, WorkItem(this->ranges[me.WorkingOnValve + valve.first] + 1, valve.first), elephant, timeLeft, released);

						if (best > bestPath)
						{
							bestPath = best;
						}
					}
				}
				return bestPath;
			}
		}
		else if (elephant.TillDone == 0)
		{
			if (std::find(Visited.begin(), Visited.end(), elephant.WorkingOnValve) == Visited.end())
			{
				if (this->importantValves[elephant.WorkingOnValve].FlowRate > 0)
				{
					released += timeLeft * this->importantValves[elephant.WorkingOnValve].FlowRate;
				}
				Visited.push_back(elephant.WorkingOnValve);
				size_t bestPath = released;
				for (auto& valve : this->importantValves)
				{
					if (std::find(Visited.begin(), Visited.end(), valve.first) == Visited.end())
					{
						auto best = SimpleBestReleaseWithElephant(Visited, me, WorkItem(this->ranges[elephant.WorkingOnValve + valve.first] + 1, valve.first), timeLeft, released);

						if (best > bestPath)
						{
							bestPath = best;
						}
					}
				}
				return bestPath;
			}
			else
			{
				size_t bestPath = released;
				for (auto& valve : this->importantValves)
				{
					if (std::find(Visited.begin(), Visited.end(), valve.first) == Visited.end())
					{
						auto best = SimpleBestReleaseWithElephant(Visited, me, WorkItem(this->ranges[elephant.WorkingOnValve + valve.first] + 1, valve.first), timeLeft, released);

						if (best > bestPath)
						{
							bestPath = best;
						}
					}
				}
				return bestPath;
			}
		}
		int remove = std::min(me.TillDone, elephant.TillDone);
		me.TillDone -= remove;
		elephant.TillDone -= remove;
		timeLeft -= remove;
	}

	return released;
}

void AOC22::Day16::Setup(InputExtractor& input)
{
	this->valves.clear();
	this->importantValves.clear();

	for (std::string row; input.NextRow(row);)
	{
		CreateValve(row);
	}

	for (auto& a : importantValves)
	{
		for (auto& b : importantValves)
		{
			if (a.first != b.first)
			{
				this->ranges[a.first + b.first] = SimpleFastestPath(std::vector<std::string>(), a.first, b.first);
				this->ranges[b.first + a.first] = this->ranges[a.first + b.first];
			}
		}
	}
}

void AOC22::Day16::CreateValve(const std::string& input)
{
	size_t start = input.find("Valve ") + 6;
	size_t end = input.find(" has");
	std::string name = input.substr(start, end - start);

	start = input.find("flow rate=") + 10;
	end = input.find("; tunnels");
	int flow_rate = stoi(input.substr(start, end - start));

	start = input.find("tunnels lead to valves ") + 23;
	if (start < 23)
	{
		start = input.find("tunnel leads to valve ") + 22;
	}
	std::string tunnel_string = input.substr(start);
	std::vector<std::string> tunnels;
	AOCCORE::RegularExpressions::RunIteratorSearch(tunnel_string, "(\\w+)", tunnels);

	this->valves[name] = Valve(name, flow_rate, tunnels);

	if (name == "AA")
	{
		this->importantValves[name] = Valve(name, flow_rate, tunnels);
	}
	if (flow_rate > 0)
	{
		this->importantValves[name] = Valve(name, flow_rate, tunnels);
	}
}

AOC22::Day16::Day16() : Day("Input//2022//day16_data.txt", "Input//2022//day16_data_simple.txt")
{
}

void AOC22::Day16::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);
	Setup(input);

	auto answer = SimpleBestRelease(std::vector<std::string>(), "AA", 30, 0);

	printf("1) (%llu)\n", answer);
}

void AOC22::Day16::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);
	Setup(input);

	auto answer = SimpleBestReleaseWithElephant(std::vector<std::string>(), WorkItem(0, "AA"), WorkItem(0, "AA"), 26, 0);

	printf("1) (%llu)\n", answer);
}

AOC22::Day16::~Day16()
{

}
