#include <algorithm>

#include "../2022/Day13_2022.h"

AOC22::Day13::Day13() : Day("Input//2022//day13_data.txt", "Input//2022//day13_data_simple.txt")
{
}

AOC22::Node AOC22::Day13::CreateNode(std::string& package)
{
	AOC22::Node node;
	std::string number;

	while (package.size() != 0)
	{
		auto c = package[0];
		package = package.substr(1);

		if (c == '[')
		{
			node.Data.push_back(CreateNode(package));
		}
		else if (c == ']')
		{
			break;
		}
		else if (c >= '0' && c <= '9')
		{
			number += c;
		}
		else if (c == ',')
		{
			if (number.size() != 0)
			{
				node.Data.push_back(stoi(number));
				number = "";
			}
		}
	}

	if (number.size() != 0)
	{
		node.Data.push_back(stoi(number));
		number = "";
	}

	return node;
}

void AOC22::Day13::PrintNode(const AOC22::Node& node)
{
	printf("[");
	for (size_t i = 0; i < node.Data.size(); i++)
	{
		if (node.Data[i].index() == 0)
		{
			printf("%i", std::get<int>(node.Data[i]));
			if (node.Data.size() != i + 1)
			{
				printf(",");
			}
		}
		else
		{
			PrintNode(std::get<AOC22::Node>(node.Data[i]));
			if (node.Data.size() != i + 1)
			{
				printf(",");
			}
		}
	}
	printf("]");
}

bool AOC22::Day13::Compare(const AOC22::Node& lhs, const AOC22::Node& rhs)
{
	if (lhs.Data.size() == 0 && rhs.Data.size() > 0)
	{
		return true;
	}
	if (lhs.Data.size() > 0 && rhs.Data.size() == 0)
	{
		return false;
	}

	for (size_t i = 0; i < lhs.Data.size(); i++)
	{
		if (i == rhs.Data.size())
		{
			return false;
		}

		// Make code easier to read.
		auto lhsIsInt = lhs.IsInt(i);
		auto rhsIsInt = rhs.IsInt(i);
		auto lhsInt = lhsIsInt ? std::get<int>(lhs.Data[i]) : -1;
		auto rhsInt = rhsIsInt ? std::get<int>(rhs.Data[i]) : -1;
		auto lhsNode = !lhsIsInt ? std::get<AOC22::Node>(lhs.Data[i]) : AOC22::Node();
		auto rhsNode = !rhsIsInt ? std::get<AOC22::Node>(rhs.Data[i]) : AOC22::Node();
		if (lhsIsInt)
		{
			lhsNode.Data.push_back(lhsInt);
		}
		if (rhsIsInt)
		{
			rhsNode.Data.push_back(rhsInt);
		}

		if (lhsIsInt && rhsIsInt)
		{
			if (lhsInt > rhsInt)
			{
				return false;
			}
			else if (lhsInt < rhsInt)
			{
				return true;
			}
			
		}
		else if (!lhsIsInt || !rhsIsInt)
		{
			auto result = Compare(lhsNode, rhsNode);

			if (result == true)
			{
				return true;
			}

			if (result == false)
			{
				return false;
			}
		}
	}

	return true;
}

void AOC22::Day13::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);
	
	AOC22::Node left;
	AOC22::Node right;

	int points = 0;
	int point = 1;
	for (std::vector<std::string> pair; input.NextBatch(pair); point++)
	{
		left = CreateNode(pair[0]);
		right = CreateNode(pair[1]);

		if (Compare(left, right))
		{
			points += point;
		}
	}

	printf("1) (%i)\n", points);
}

void AOC22::Day13::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	int points = 1;

	std::vector<AOC22::Node> ordered;
	for (std::string row; input.NextRow(row);)
	{
		if (row == "")
		{
			continue;
		}
		row = row.substr(1, row.size() - 1);
		auto toAdd = CreateNode(row);
		if (ordered.empty())
		{
			ordered.push_back(toAdd);
			continue;
		}
		bool added = false;
		for (size_t i = 0; i < ordered.size(); i++)
		{
			if (Compare(toAdd, ordered[i]))
			{
				ordered.insert(ordered.begin() + i, toAdd);
				added = true;
				break;
			}
		}
		if (!added)
		{
			ordered.push_back(toAdd);
		}
	}

	std::string s2 = "[2]";
	std::string s6 = "[6]";

	std::vector<AOC22::Node> toAdd;
	toAdd.push_back(CreateNode(s2));
	toAdd.push_back(CreateNode(s6));

	for (int add = 0, insert = 0; insert < ordered.size(); insert++)
	{
		if (Compare(toAdd[add], ordered[insert]))
		{
			ordered.insert(ordered.begin() + insert, toAdd[add]);
			points *= (insert + 1);
			add++;
			if (add == 2)
			{
				break;
			}
		}
	}

	printf("2) (%i)\n", points);
}

AOC22::Day13::~Day13()
{

}
