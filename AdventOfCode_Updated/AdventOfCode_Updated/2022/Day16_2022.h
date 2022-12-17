#pragma once
#include <unordered_map>

#include "../Day.h"

namespace AOC22
{
	namespace DAY16
	{
		struct Valve
		{
			std::string Name;
			size_t FlowRate;
			std::vector<std::string> CanAccessTunnels;

			Valve()
			{
				Name = "";
				FlowRate = 0;
			}

			Valve(std::string name,  size_t flowRate, std::vector<std::string> canAccess) : Name(name), FlowRate(flowRate)
			{
				for (auto& tunnel : canAccess)
				{
					CanAccessTunnels.push_back(tunnel);
				}
			}
		};

		struct WorkItem
		{
			int TillDone;
			std::string WorkingOnValve;

			WorkItem(int tillDone, std::string workingOnValve) : TillDone(tillDone), WorkingOnValve(workingOnValve)
			{
			}
		};
	}
	using namespace DAY16;

	typedef std::unordered_map<std::string, Valve> ValveMap;
	typedef std::unordered_map<std::string, int> RangeMap;

	class Day16 : public Day
	{
	private:
		ValveMap valves;
		ValveMap importantValves;
		RangeMap ranges;
		int needToClose = 0;

		size_t SimpleFastestPath(std::vector<std::string>, std::string, std::string);
		size_t SimpleBestRelease(std::vector<std::string>, std::string, int, size_t);
		size_t SimpleBestReleaseWithElephant(std::vector<std::string>, WorkItem, WorkItem, int, size_t);

		void Setup(InputExtractor&);
		void CreateValve(const std::string&);
	public:
		Day16();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day16();
	};
}
