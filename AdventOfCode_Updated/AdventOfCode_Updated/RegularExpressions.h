#pragma once
#include <string>
#include <vector>

namespace AOCCORE
{
	static class RegularExpressions
	{
	public:
		bool static RunSearch(const std::string, const std::string, std::vector<std::string>&);
		bool static RunIteratorSearch(const std::string, const std::string, std::vector<std::string>&);
	};
}

