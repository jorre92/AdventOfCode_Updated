#include "Day04_2020.h"
#include "RegularExpressions.h"

bool AOC20::Day04::ValidateData(size_t key, const std::string& value) const
{
	bool foundValid = true;
	size_t year = 0;
	std::vector<std::string> results;
	switch (key)
	{
	case 0: //byr
		year = std::stoi(value);
		foundValid = year <= 2002 && year >= 1920;
		break;
	case 1: //iyr
		year = std::stoi(value);
		foundValid = year <= 2020 && year >= 2010;
		break;
	case 2: //eyr
		year = std::stoi(value);
		foundValid = year <= 2030 && year >= 2020;
		break;
	case 3: //hgt
		foundValid = AOCCORE::RegularExpressions::RunSearch(value, "([0-9]+)(cm|in)", results);

		if (foundValid)
		{
			auto temp = std::stoi(results[1]);
			if (results[2] == "cm")
			{
				foundValid = temp <= 193 && temp >= 150;
			}
			else
			{
				foundValid = temp <= 76 && temp >= 59;
			}
		}
		break;
	case 4:
		foundValid = AOCCORE::RegularExpressions::RunSearch(value, "#([0-9a-f]+)", results) && results[1].length() == 6;
		break;
	case 5: //ecl
		foundValid = AOCCORE::RegularExpressions::RunSearch(value, "(amb|blu|brn|gry|grn|hzl|oth)", results);
		break;
	case 6: //pid
		foundValid = AOCCORE::RegularExpressions::RunSearch(value, "([0-9]+)", results) && results[1].length() == 9 && value.length() == 9;
		break;
	default:
		break;
	}

	return foundValid;
}

AOC20::Day04::Day04() : Day("2020//Input//day04_data.txt", "2020//Input//day04_data_simple.txt")
{
	_name = __func__;

	_requredFields.push_back("byr");
	_requredFields.push_back("iyr");
	_requredFields.push_back("eyr");
	_requredFields.push_back("hgt");
	_requredFields.push_back("hcl");
	_requredFields.push_back("ecl");
	_requredFields.push_back("pid");
}

void AOC20::Day04::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);

	size_t validPassports = 0;

	for (std::string batch; input.NextBatch(batch);)
	{
		std::vector<std::string> regExResults;
		bool valid = true;
		
		if (!AOCCORE::RegularExpressions::RunIteratorSearch(batch, "(\\w+)", regExResults))
		{
			continue;
		}

		for (auto requred : _requredFields)
		{
			if (std::find(regExResults.begin(), regExResults.end(), requred) == regExResults.end())
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			validPassports++;
		}
	}

	printf("[%s-%s] : Valid passports {%d}.\n", _name.c_str(), __func__, validPassports);
}

void AOC20::Day04::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);

	size_t validPassports = 0;

	for (std::string batch; input.NextBatch(batch);)
	{
		std::vector<std::string> regExResults;
		bool valid = true;

		if (!AOCCORE::RegularExpressions::RunIteratorSearch(batch, "(#\\w+|\\w+)", regExResults))
		{
			continue;
		}

		for (int fieldIndex = 0; fieldIndex < _requredFields.size(); ++fieldIndex)
		{
			auto found = std::find(regExResults.begin(), regExResults.end(), _requredFields[fieldIndex]);
			if (found == regExResults.end() || !ValidateData(fieldIndex, *(found+1)))
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			validPassports++;
		}
	}

	printf("[%s-%s] : Valid passports {%d}.\n", _name.c_str(), __func__, validPassports);
}

AOC20::Day04::~Day04()
{
}