#pragma once

#include "../Day.h"
#include "../CalenderDay.h"

namespace AOC19
{
	class Calander
	{
	public:
		Day* CreateSolution(AOCCORE::CalenderDay) const;
		void DestroySolution(Day*) const;
	};
}
