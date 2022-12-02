#pragma once
#include "../Day.h"

namespace AOC20
{
	class ValidSpann
	{
	private:
		std::string _name;
		size_t _minA, _maxA, _minB, _maxB;
	public:
		std::string Name() const { return _name; }
		ValidSpann(std::string name, size_t minA, size_t maxA, size_t minB, size_t maxB) : _minA(minA), _maxA(maxA), _minB(minB), _maxB(maxB), _name(name) {}
		bool Valid(size_t value) const { return ((value >= _minA) && (value <= _maxA)) || ((value >= _minB) && (value <= _maxB)); }
		bool operator==(const ValidSpann& other) { return other.Name() == _name; }
	};

	class Day16 : public Day
	{
	public:
		std::vector<ValidSpann> _validSpanns;
		bool IsValidTicket(const std::string, std::vector<size_t>&) const;
		void UpdateValidSpanns(const std::vector<std::string>&);
	public:
		Day16();

		void SolvePartOne(bool simpleData);
		void SolvePartTwo(bool simpleData);

		~Day16();
	};
}