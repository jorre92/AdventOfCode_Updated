#include "InputExtractor.h"
#include <iostream>

InputExtractor::InputExtractor(std::string filePath) : _stream(filePath), _filePath(filePath)
{
	//printf("Construction of %s object, file{%s}.\n", __func__, filePath.c_str());

	if (_stream && !(_stream.good() && _stream.is_open()))
	{
		printf("Failed to initialize stream.\n");
	}
}

InputExtractor::InputExtractor(const InputExtractor&)
{
	//printf("Copy construction of %s object.\n", __func__);
}

template<typename T>
bool InputExtractor::Next(T& item)
{
	if (!_stream.is_open() || _stream.eof())
	{
		return false;
	}

	if (_stream >> item)
	{
		return true;
	}

	return false;
}

bool InputExtractor::NextRow(std::string& row)
{
	if (!_stream.is_open() || _stream.eof())
	{
		return false;
	}

	if (std::getline(_stream, row))
	{
		return true;
	}

	return false;
}

bool InputExtractor::NextBatch(std::vector<std::string>& batch)
{
	if (!_stream.is_open() || _stream.eof())
	{
		return false;
	}

	batch.clear();

	for (std::string row; NextRow(row) && row != "";)
	{
		batch.push_back(row);
	}

	return true;
}

bool InputExtractor::NextBatch(std::string& batch)
{
	if (!_stream.is_open() || _stream.eof())
	{
		return false;
	}

	batch = "";

	for (std::string row; NextRow(row) && row != "";)
	{
		batch += row+"\n";
	}

	return true;
}

void InputExtractor::Reset()
{
	_stream.clear();
	_stream.seekg(0, std::ios::beg);
}

InputExtractor::~InputExtractor()
{
	if (&_stream == nullptr)
	{
		_stream = std::ifstream{ _filePath };
	}
}


template bool InputExtractor::Next(std::string&);
template bool InputExtractor::Next(int&);
template bool InputExtractor::Next(uintmax_t&);
template bool InputExtractor::Next(uint64_t&);
template bool InputExtractor::Next(size_t&);
template bool InputExtractor::Next(char&);
template bool InputExtractor::Next(float&);
template bool InputExtractor::Next(double&);