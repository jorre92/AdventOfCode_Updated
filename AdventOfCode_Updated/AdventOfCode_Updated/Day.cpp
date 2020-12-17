#include "Day.h"

#include <iostream>
#include <fstream>

InputExtractor Day::Input(bool simple)
{
	return InputExtractor(simple ? _simpleData : _data);
}

Day::Day(std::string filePath, std::string simpleFilePath) : _data(filePath), _simpleData(simpleFilePath)
{
	//printf("Construction of %s object, data{%s}, simple data{%s}.\n", __func__, filePath.c_str(), simpleFilePath.c_str());
}

Day::~Day()
{
	//printf("Destruction of %s object.\n", __func__);
}


