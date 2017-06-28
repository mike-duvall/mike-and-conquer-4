#pragma once



#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include <string>
//#include <exception>
#include "dxerr.h"
#include "StackTrace.h"


class DirectXError : public std::exception
{
public:
	HRESULT hresult;
	std::string message;
	std::string stacktrace;
	std::string dxErrorString;
	std::string dxErrorDescription;

public:

	DirectXError(HRESULT aHresult, std::string aMessage) {
		this->hresult = aHresult;
		this->message = aMessage;
		dxErrorString = DXGetErrorString(hresult);
		dxErrorDescription = DXGetErrorDescription(hresult);
		int numFramesToSkip = 2;
		stacktrace = StackTrace::createStackTrace(numFramesToSkip);
	}

};


