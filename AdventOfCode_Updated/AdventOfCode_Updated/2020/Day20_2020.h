#pragma once
#include "../Day.h"
#include "../CameraView.h"

namespace AOC20
{
	class Day20 : public Day
	{
	private:
		std::vector<CameraView> _cameraViews;
		CameraView& GetCameraByID(size_t);
	public:
		Day20();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day20();
	};
}