#pragma once
#include <string>
#include <vector>

namespace AOCCORE
{
	class RegularExpressions
	{
	public:
		static bool RunSearch(const std::string text, const std::string regEx, std::string& result);
		static bool RunSearch(const std::string text, const std::string regEx, std::vector<std::string>& results);
		static bool RunIteratorSearch(const std::string text, const std::string regEx, std::vector<std::string>& results);
	};
}

