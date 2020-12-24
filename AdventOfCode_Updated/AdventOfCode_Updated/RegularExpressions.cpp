#include "RegularExpressions.h"
#include <regex>
#include <iostream>

bool AOCCORE::RegularExpressions::RunSearch(const std::string string, const std::string regEx, std::string& result)
{
	std::regex regex(regEx);
	std::smatch match;
	result = "";
	
	auto found = std::regex_search(string, match, regex);

	if (found)
	{
		result = match[1];
	}

	return found;
}

bool AOCCORE::RegularExpressions::RunSearch(const std::string string, const std::string regEx, std::vector<std::string>& results)
{
	std::regex regex(regEx);
	std::smatch matches;
	results.clear(); 

	std::regex_search(string, matches, regex);

	for (auto it = matches.begin(); it != matches.end(); ++it)
	{
		results.push_back((*it).str());
	}

	return !results.empty();
}

bool AOCCORE::RegularExpressions::RunIteratorSearch(const std::string s, const std::string regEx, std::vector<std::string>& results)
{
	std::regex regex(regEx);
	results.clear();

	std::sregex_iterator wordBegin(s.begin(), s.end(), regex);
	std::sregex_iterator wordEnd;

	for (auto it = wordBegin; it != wordEnd; ++it)
	{
		results.push_back((*it).str());
	}

	return !results.empty();
}
