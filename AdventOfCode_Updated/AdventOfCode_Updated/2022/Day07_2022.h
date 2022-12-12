#pragma once

#include "../Day.h"

namespace AOC22
{
	struct file
	{
		std::string name;
		size_t size = 0;

		void PrintFile(std::string);
	};

	struct dir
	{
		std::string name;
		dir* parent = this;
		std::vector<struct dir> dirs;
		std::vector<struct file> files;

		void PrintDir(std::string);
		size_t TotalSizeOfFiles();
		size_t TotalSizeOfDir();

		size_t TotalSizeOfDirsUnder(size_t);
		std::vector<dir> GetAllDirs();
	};

	class Day07 : public Day
	{
	private:
		dir GenerateDir(const std::vector<std::string>&);
	public:
		Day07();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day07();
	};
}
