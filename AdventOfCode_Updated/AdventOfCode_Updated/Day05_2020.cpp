#include "Day05_2020.h"
#include "RegularExpressions.h"
#include <algorithm>

AOC20::Day05::Day05() : Day("2020//Input//day05_data.txt", "2020//Input//day05_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day05::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);
	int highestSeatId = 0;

	for (std::string BoardingInformation; input.NextRow(BoardingInformation);)
	{
		std::string rowDetails(BoardingInformation.substr(0, 7));
		std::string seatDetails(BoardingInformation.substr(7, 9));
		
		int rowNumber(0), seatNumber(0), seatId(0), index(0);

		for (; index < seatDetails.length(); ++index)
		{
			rowNumber += rowDetails[index] == 'B' ? pow(2, rowDetails.length() - index - 1) : 0;
			seatNumber += seatDetails[index] == 'R' ? pow(2, seatDetails.length() - index - 1) : 0;
		}
		for (; index < rowDetails.length(); ++index)
		{
			rowNumber += rowDetails[index] == 'B' ? pow(2, rowDetails.length() - index - 1) : 0;
		}

		seatId = rowNumber * 8 + seatNumber;

		highestSeatId = seatId > highestSeatId ? seatId : highestSeatId;
	}

	printf("[%s-%s] : Highest seat id found {%d}.\n", _name.c_str(), __func__, highestSeatId);
}

void AOC20::Day05::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);

	std::vector<int> seatIds;

	for (std::string BoardingInformation; input.NextRow(BoardingInformation);)
	{
		std::string rowDetails(BoardingInformation.substr(0, 7));
		std::string seatDetails(BoardingInformation.substr(7, 9));

		int rowNumber(0), seatNumber(0), seatId(0), index(0);

		for (; index < seatDetails.length(); ++index)
		{
			rowNumber += rowDetails[index] == 'B' ? pow(2, rowDetails.length() - index - 1) : 0;
			seatNumber += seatDetails[index] == 'R' ? pow(2, seatDetails.length() - index - 1) : 0;
		}
		for (; index < rowDetails.length(); ++index)
		{
			rowNumber += rowDetails[index] == 'B' ? pow(2, rowDetails.length() - index - 1) : 0;
		}

		seatId = rowNumber * 8 + seatNumber;

		seatIds.push_back(seatId);
	}

	std::sort(seatIds.begin(), seatIds.end());

	for (size_t i = 0; i < seatIds.size()-1; i++)
	{
		if (seatIds[i] - seatIds[i+1] == -2)
		{
			printf("[%s-%s] : Tour seat id is {%d}.\n", _name.c_str(), __func__, seatIds[i]+1);
			break;
		}
	}

}

AOC20::Day05::~Day05()
{
}