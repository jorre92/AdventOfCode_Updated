#include "Day21_2020.h"
#include "RegularExpressions.h"

#include <set>
#include <map>
#include <algorithm>

void AOC20::Day21::SortMenuItems(const std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>& menu, const std::string& filter, std::vector<std::string>& match, std::vector<std::string>& notMatched)
{
	for (auto item : menu)
	{
		auto found = std::find(item.first.begin(), item.first.end(), filter);
		if (found != item.first.end())
		{
			match.insert(match.end(), item.second.begin(), item.second.end());
		}
		else
		{
			notMatched.insert(notMatched.end(), item.second.begin(), item.second.end());
		}
	}

	std::sort(match.begin(), match.end());
	std::sort(notMatched.begin(), notMatched.end());
	match.erase(std::unique(match.begin(), match.end()), match.end());
	notMatched.erase(std::unique(notMatched.begin(), notMatched.end()), notMatched.end());
}

AOC20::Day21::Day21() : Day("2020//Input//day21_data.txt", "2020//Input//day21_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day21::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);

	std::map<std::string, std::vector<std::string>> potentialAllergen;
	std::map<std::string, uint64_t> ingredientCount;

	for (std::string s; input.NextRow(s);)
	{
		std::vector<std::string> results, ingredients, allergies;
		AOCCORE::RegularExpressions::RunSearch(s, "(.*)[(]contains (.*)[)]", results);


		AOCCORE::RegularExpressions::RunIteratorSearch(results[1], "([a-z]+)", ingredients);
		AOCCORE::RegularExpressions::RunIteratorSearch(results[2], "([a-z]+)", allergies);

		for (auto i : ingredients)
		{
			if (ingredientCount.find(i) != ingredientCount.end())
			{
				ingredientCount[i] += 1;
			}
			else
			{
				ingredientCount.insert({ i, 1 });
			}
		}

		for (auto a : allergies)
		{
			if (potentialAllergen.find(a) != potentialAllergen.end())
			{
				auto temp = potentialAllergen[a];
				potentialAllergen[a].clear();

				for (auto t : temp)
				{
					if (std::find(ingredients.begin(), ingredients.end(), t) != ingredients.end())
					{
						potentialAllergen[a].push_back(t);
					}
				}

				std::sort(potentialAllergen[a].begin(), potentialAllergen[a].end());
				potentialAllergen[a].erase(unique(potentialAllergen[a].begin(), potentialAllergen[a].end()), potentialAllergen[a].end());
			}
			else
			{
				potentialAllergen.insert({ a, ingredients });
			}
		}
	}


	uint64_t sum = 0;

	for (auto i : ingredientCount)
	{
		auto contains = false;
		for (auto a : potentialAllergen)
		{
			auto found = std::find(a.second.begin(), a.second.end(), i.first);
			if (found != a.second.end())
			{
				contains = true;
				break;
			}
		}


		if (!contains)
		{
			sum += i.second;
		}
	}

	printf("[%s-%s] : Number of ingrediens {%llu}.\n", _name.c_str(), __func__, sum);
}

void AOC20::Day21::SolvePartTwo(bool simpleData)
{

	auto input = Day::Input(simpleData);

	std::map<std::string, std::vector<std::string>> potentialAllergen;
	std::map<std::string, uint64_t> ingredientCount;

	for (std::string s; input.NextRow(s);)
	{
		std::vector<std::string> results, ingredients, allergies;
		AOCCORE::RegularExpressions::RunSearch(s, "(.*)[(]contains (.*)[)]", results);


		AOCCORE::RegularExpressions::RunIteratorSearch(results[1], "([a-z]+)", ingredients);
		AOCCORE::RegularExpressions::RunIteratorSearch(results[2], "([a-z]+)", allergies);

		for (auto a : allergies)
		{
			if (potentialAllergen.find(a) != potentialAllergen.end())
			{
				auto temp = potentialAllergen[a];
				potentialAllergen[a].clear();

				for (auto t : temp)
				{
					if (std::find(ingredients.begin(), ingredients.end(), t) != ingredients.end())
					{
						potentialAllergen[a].push_back(t);
					}
				}

				std::sort(potentialAllergen[a].begin(), potentialAllergen[a].end());
				potentialAllergen[a].erase(unique(potentialAllergen[a].begin(), potentialAllergen[a].end()), potentialAllergen[a].end());
			}
			else
			{
				potentialAllergen.insert({ a, ingredients });
			}
		}
	}

	bool updated = true;

	while (updated)
	{
		updated = false;
		for (auto& a : potentialAllergen)
		{
			if (a.second.size() == 1)
			{
				for (auto& other : potentialAllergen)
				{
					if (a != other)
					{
						auto found = std::find(other.second.begin(), other.second.end(), a.second[0]);
						if (found != other.second.end())
						{
							other.second.erase(found);
							updated = true;
						}
					}
				}
			}
		}
	}

	std::string answer = "";
	for (auto s : potentialAllergen)
	{
		answer += s.second[0] + ",";
	}
	answer.erase(answer.end() - 1);
	printf("[%s-%s] : Number of ingrediens {%s}.\n", _name.c_str(), __func__, answer.c_str());
}

AOC20::Day21::~Day21()
{
}