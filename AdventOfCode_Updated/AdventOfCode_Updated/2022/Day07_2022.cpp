#include <iostream>

#include "../2022/Day07_2022.h"

#include "../RegularExpressions.h"

AOC22::dir AOC22::Day07::GenerateDir(const std::vector<std::string>& cmdText)
{
	std::string dirRegEx = "\\$ cd (.*)";
	std::string fileRegEx = "(\\d+)\\s+(.*)";

	dir fileSystem;
	dir* currentPosition = 0;

	for (auto row : cmdText)
	{
		std::string dirName;
		std::vector<std::string> fileData;
		if (AOCCORE::RegularExpressions::RunSearch(row, dirRegEx, dirName))
		{
			if (currentPosition == 0)
			{
				fileSystem.name = dirName;
				currentPosition = &fileSystem;
			}
			else if (dirName == "..")
			{
				currentPosition = currentPosition->parent;
			}
			else
			{
				dir newDir;
				newDir.name = dirName;
				newDir.parent = currentPosition;
				currentPosition->dirs.push_back(newDir);
				currentPosition = &(currentPosition->dirs.back());
			}
		}
		else if (AOCCORE::RegularExpressions::RunSearch(row, fileRegEx, fileData))
		{
			file newFile;
			newFile.name = fileData[2];
			newFile.size = std::stoi(fileData[1]);
			currentPosition->files.push_back(newFile);
		}
	}

	return fileSystem;
}

void AOC22::file::PrintFile(std::string prefix)
{
	std::cout << prefix << name << " (file, size=" << size << ")" << std::endl;
}

void AOC22::dir::PrintDir(std::string prefix)
{
	dir* currentDir;
	currentDir = this;

	std::cout << prefix << name << " (dir, size=" << TotalSizeOfDir() << ")" << std::endl;

	for (auto dir : dirs)
	{
		dir.PrintDir(" " +prefix);
	}

	for (auto file : files)
	{
		file.PrintFile(" " + prefix);
	}
}

size_t AOC22::dir::TotalSizeOfFiles()
{
	size_t size = 0;

	for (auto file : files)
	{
		size += file.size;
	}

	return size;
}

size_t AOC22::dir::TotalSizeOfDir()
{
	auto dirSize = 0;
	auto fileSize = TotalSizeOfFiles();

	for (auto dir : dirs)
	{
		dirSize += dir.TotalSizeOfDir();
	}

	return fileSize + dirSize;
}

size_t AOC22::dir::TotalSizeOfDirsUnder(size_t maxSize)
{
	auto returnSize = 0;
	auto thisDirSize = TotalSizeOfDir();
	
	if (thisDirSize > maxSize)
	{
		thisDirSize = 0;
	}

	for (auto dir : dirs)
	{
		returnSize += dir.TotalSizeOfDirsUnder(maxSize);
	}

	return returnSize + thisDirSize;
}

std::vector<AOC22::dir> AOC22::dir::GetAllDirs()
{
	std::vector<dir> allDirs;
	allDirs.push_back(*this);

	for (auto dir : dirs)
	{
		auto moreDirs = dir.GetAllDirs();

		allDirs.insert(allDirs.end(), moreDirs.begin(), moreDirs.end());
	}

	return allDirs;
}

AOC22::Day07::Day07() : Day("Input//2022//day07_data.txt", "Input//2022//day07_data_simple.txt")
{
	
}

void AOC22::Day07::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<std::string> cmdText;

	if (input.NextBatch(cmdText))
	{
		struct dir myFileSystem = GenerateDir(cmdText);

		//myFileSystem.PrintDir("- ");

		auto size = myFileSystem.TotalSizeOfDirsUnder(100000);

		std::cout << size << std::endl;
	}
}


void AOC22::Day07::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<std::string> cmdText;

	if (input.NextBatch(cmdText))
	{
		struct dir myFileSystem = GenerateDir(cmdText);

		//myFileSystem.PrintDir("- ");

		auto size = myFileSystem.TotalSizeOfDir();

		size_t maxSizeOfFileSystem = 70000000 - 30000000;
		size_t toRemoveMin = size - maxSizeOfFileSystem;

		std::cout << "Need to remove at least : " << size - maxSizeOfFileSystem << std::endl;

		auto allDirs = myFileSystem.GetAllDirs();
		auto currentDirToRemove = myFileSystem;
		size_t currentSmallest = currentDirToRemove.TotalSizeOfDir();

		for (auto dir : allDirs)
		{
			auto sizeOfDir = dir.TotalSizeOfDir();
			if (sizeOfDir > toRemoveMin && sizeOfDir < currentSmallest)
			{
				currentDirToRemove = dir;
				currentSmallest = sizeOfDir;
			}
		}

		std::cout << currentDirToRemove.name << " - " << currentSmallest << std::endl;
	}

}

AOC22::Day07::~Day07()
{
}