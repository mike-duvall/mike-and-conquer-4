#include "StackTrace.h"


#define WIN32_LEAN_AND_MEAN

#include "windows.h"


#include "dbghelp.h"

#define TRACE_MAX_STACK_FRAMES 1024
#define TRACE_MAX_FUNCTION_NAME_LENGTH 1024

#include <stdio.h>
#include <Windows.h>

#define BUFSIZE MAX_PATH

#include <tchar.h>



std::string StackTrace::createStackTrace(int numFramesToSkip)
{
	void *stack[TRACE_MAX_STACK_FRAMES];
	HANDLE process = GetCurrentProcess();

	SymInitialize(process, nullptr, TRUE);

	char path[255];
	SymGetSearchPath(process, path, 255);

	//TCHAR Buffer[BUFSIZE];
	//DWORD dwRet = GetCurrentDirectory(BUFSIZE, Buffer);


	WORD numberOfFrames = CaptureStackBackTrace(0, TRACE_MAX_STACK_FRAMES, stack, NULL);
	SYMBOL_INFO *symbol = (SYMBOL_INFO *)malloc(sizeof(SYMBOL_INFO) + (TRACE_MAX_FUNCTION_NAME_LENGTH - 1) * sizeof(TCHAR));
	symbol->MaxNameLen = TRACE_MAX_FUNCTION_NAME_LENGTH;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	DWORD displacement;
	IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
	line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);

	std::string stackTrace = "";

	for (int i = numFramesToSkip; i < numberOfFrames; i++)
	{
		DWORD64 address = (DWORD64)(stack[i]);
		SymFromAddr(process, address, NULL, symbol);
		if (SymGetLineFromAddr64(process, address, &displacement, line))
		{
			char buffer[500];
			sprintf(buffer, "\tat %s in %s: line: %lu: address: 0x%0X\n", symbol->Name, line->FileName, line->LineNumber, symbol->Address);
			//printf("\tat %s in %s: line: %lu: address: 0x%0X\n", symbol->Name, line->FileName, line->LineNumber, symbol->Address);
			stackTrace += buffer;
		}
		else
		{
			char buffer1[500];
			sprintf(buffer1, "\tSymGetLineFromAddr64 returned error code %lu.\n", GetLastError());
			printf("\tSymGetLineFromAddr64 returned error code %lu.\n", GetLastError());

			char buffer2[500];
			sprintf(buffer2, "\tat %s, address 0x%0X.\n", symbol->Name, symbol->Address);
			stackTrace += buffer2;
			//printf("\tat %s, address 0x%0X.\n", symbol->Name, symbol->Address);

		}

	}
	return stackTrace;
}
