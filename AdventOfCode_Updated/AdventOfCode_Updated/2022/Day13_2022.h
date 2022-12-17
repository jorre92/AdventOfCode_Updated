#pragma once

#include "../Day.h"
#include <variant>


namespace AOC22
{
	struct Node
	{
		std::vector<std::variant<int, AOC22::Node>> Data;

		bool IsInt(size_t index) const { return this->Data[index].index() == 0; }
		bool IsNode(size_t index) const { return this->Data[index].index() == 0; }

		int GetInt(size_t index) const { return std::get<int>(this->Data[index]); }
	};

	class Day13 : public Day
	{
	private:

		AOC22::Node CreateNode(std::string&);
		void PrintNode(const AOC22::Node&);
		static bool Compare(const AOC22::Node&, const AOC22::Node&);
	public:
		Day13();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day13();
	};
}
