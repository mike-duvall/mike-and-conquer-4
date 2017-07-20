#pragma once


#include <string>

class StackTrace {
	
public:

	static std::string createStackTrace(int numFramesToSkip);
};