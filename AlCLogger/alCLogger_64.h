#pragma once


#include <windows.h>
#include <tchar.h>
#include <iostream>

#include <fstream>
#include <ctime>
#include <mutex>

using namespace std;


#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif

#ifndef DLLIMPORT
#define DLLIMPORT __declspec(dllimport)
#endif

//FWD Decl
class AlCLogger;

DLLEXPORT AlCLogger *getGlobalAlCLogger();
DLLEXPORT void setGlobalAlCLogger(AlCLogger *vLogger);

DLLEXPORT bool getGlobalDebugSetting();
DLLEXPORT void setGlobalDebugSetting(bool vDebug);


//The logging class allows for console and file logging.
class DLLEXPORT AlCLogger
{
private:
	//Indicates if we are debugging or not.
	bool DEBUG_FLAG;
	LPWSTR logFileName;
	wofstream *file;
	time_t rawtime;
	tm timeinfo;

	char ltbuf[80];
	wchar_t ltbuft[80];

	char ltbufB[4096];
	wchar_t ltbufBT[4096];

	std::mutex allogmutex;

public:
	AlCLogger(LPWSTR logFileNameX, bool debugFlag);
	~AlCLogger();


	//Logs a msg to CONSOLE/FILE.
	void debug(LPSTR msg);
	void debug(LPWSTR msg);

};

