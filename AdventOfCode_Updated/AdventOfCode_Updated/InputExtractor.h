#pragma once

#include <string>
#include <vector>
#include <fstream>

class InputExtractor
{
private:
	std::string _filePath;
	std::ifstream _stream;
public:
	InputExtractor(std::string);
	InputExtractor(const InputExtractor&);

	template<typename T>
	bool Next(T&);
	bool NextRow(std::string&);
	bool NextBatch(std::vector<std::string>&);
	bool NextBatch(std::string&);

	void Reset();

	~InputExtractor();
};