#include "Day16_2020.h"
#include "RegularExpressions.h"
#include <regex>

bool AOC20::Day16::IsValidTicket(const std::string ticket, std::vector<size_t>& failedOn) const
{
	bool valid = true;
	std::string rx = "([0-9]+)";
	std::vector<std::string> results;
	AOCCORE::RegularExpressions regEx;

	if (regEx.RunIteratorSearch(ticket, rx, results))
	{
		for (auto& result : results)
		{
			size_t res = std::stoi(result);
			auto anyValidSpann = false;

			for (auto spann : _validSpanns)
			{
				if (spann.Valid(res))
				{
					anyValidSpann = true;
				}
			}

			if (!anyValidSpann)
			{
				valid = false;
				failedOn.push_back(res);
			}
		}
	}

	return valid;
}

void AOC20::Day16::UpdateValidSpanns(const std::vector<std::string>& batch)
{
	AOCCORE::RegularExpressions regEx;
	std::string regularExpression = "(.*): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)";

	_validSpanns.clear();
	for (auto rule : batch)
	{
		std::vector<std::string> results;

		if (regEx.RunSearch(rule, regularExpression, results))
		{
			_validSpanns.push_back(ValidSpann(results[1], std::stoi(results[2]), std::stoi(results[3]), std::stoi(results[4]), std::stoi(results[5])));
		}
	}
}

AOC20::Day16::Day16() : Day("2020//Input//day16_data.txt", "2020//Input//day16_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day16::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);

	std::vector<std::string> batch;
	if (input.NextBatch(batch))
	{
		UpdateValidSpanns(batch);
	}

	if (input.NextBatch(batch)) {} // my ticket ignore.

	uint64_t sum = 0;
	if (input.NextBatch(batch))
	{
		for (auto ticket : batch)
		{
			std::vector<size_t> failed;
			if (!IsValidTicket(ticket, failed))
			{
				for (auto fail : failed)
				{
					sum += fail;
				}
			}
		}
	}

	printf("[%s-%s] : Sum of invalid ticket fields {%llu}.\n", _name.c_str(), __func__, sum);
}

void AOC20::Day16::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);
	AOCCORE::RegularExpressions regEx;
	std::vector<std::string> batch;

	std::vector<size_t> myTicket;
	std::vector<std::vector<size_t>> otherTickets;
	std::vector<std::vector<ValidSpann>> validSpannsForField;

	if (input.NextBatch(batch))
	{
		UpdateValidSpanns(batch);
	}

	// my ticket
	if (input.NextBatch(batch))
	{
		auto line = batch[1];
		std::vector<std::string> results;
		if (regEx.RunIteratorSearch(line, "([0-9]+)", results))
		{
			for (auto number : results)
			{
				myTicket.push_back(std::stoi(number));
				validSpannsForField.push_back(_validSpanns);
			}
		}
	}

	// other tickets
	if (input.NextBatch(batch))
	{
		for (auto line : batch)
		{
			std::vector<std::string> results;
			std::vector<size_t> failedOn;
			std::vector<size_t> ticketNumbers;

			if (!(regEx.RunIteratorSearch(line, "([0-9]+)", results) && IsValidTicket(line, failedOn)))
			{
				continue;
			}

			for (int numberIndex = 0; numberIndex < results.size(); ++numberIndex)
			{
				ticketNumbers.push_back(std::stoi(results[numberIndex]));

				for (int i = 0; i < validSpannsForField[numberIndex].size(); ++i)
				{
					if (validSpannsForField[numberIndex][i].Valid(ticketNumbers.back()))
					{
						continue;
					}

					validSpannsForField[numberIndex].erase(validSpannsForField[numberIndex].begin() + i);
					i--;
				}
			}

			otherTickets.push_back(ticketNumbers);
		}
	}

	std::vector<size_t> done;

	for (int fieldIndex = 0; fieldIndex < validSpannsForField.size(); ++fieldIndex)
	{
		if (!(validSpannsForField[fieldIndex].size() == 1 && 
			std::find(done.begin(), done.end(), fieldIndex) == done.end()))
		{
			continue;
		}

		done.push_back(fieldIndex);
		auto spann = validSpannsForField[fieldIndex].back();
			
		for (int i = 0; i < validSpannsForField.size(); ++i)
		{
			if (!(i != fieldIndex && std::find(done.begin(), done.end(), i) == done.end()))
			{
				continue;
			}

			auto match = std::find(validSpannsForField[i].begin(), validSpannsForField[i].end(), spann);

			if (match != validSpannsForField[i].end())
			{
				validSpannsForField[i].erase(match);
			}
			
		}
		fieldIndex = 0;
	}

	uint64_t product = 1;
	for (int i = 0; i < validSpannsForField.size(); ++i)
	{
		auto spann = validSpannsForField[i].front();
		if (spann.Name().find("departure") != std::string::npos)
		{
			product *= myTicket[i];
		}
	}

	printf("[%s-%s] : The product of fields on my ticket is {%llu}.\n", _name.c_str(), __func__, product);
}

AOC20::Day16::~Day16()
{
}