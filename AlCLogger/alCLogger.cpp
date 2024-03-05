#include "alCLogger_64.h"

AlCLogger *globalInstance = NULL;
bool globalDebug = true;

AlCLogger *getGlobalAlCLogger() { return globalInstance; };
void setGlobalAlCLogger(AlCLogger *vLogger) { globalInstance = vLogger; };

bool getGlobalDebugSetting() { return globalDebug; };
void setGlobalDebugSetting(bool vDebug) { globalDebug = vDebug; } ;


//Constructor.
AlCLogger::AlCLogger(LPWSTR logFileNameX, bool debugFlag)
{
	DEBUG_FLAG = debugFlag;
	logFileName = logFileNameX;
	file = NULL;

	if (logFileName == NULL)
		return;
	
	//Init the fstream
	if (file == NULL) {
		DeleteFile(logFileName);
		file = new wofstream(logFileName, ios::out | ios::app);
	}

	
}

//Destructor.
AlCLogger::~AlCLogger()
{
	if (file != NULL)
		file->close();

}

//Logs a msg to CONSOLE / FILE.
void AlCLogger::debug(LPSTR msg) 
{
	std::lock_guard<std::mutex> lmut(allogmutex);

	if (!DEBUG_FLAG)
		return;

	ZeroMemory(ltbuf, sizeof(char) * 80);
	ZeroMemory(ltbufB, sizeof(char)* 4096);

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(ltbuf, 80, "%d-%m-%Y %I:%M:%S \0", &timeinfo);
	strcpy_s(ltbufB, ltbuf);
	strcat_s(ltbufB, msg);

	cout << ltbufB;


	*file << ltbufB;
	file->flush();
	
}

void AlCLogger::debug(LPWSTR msg) 
{
	std::lock_guard<std::mutex> lmut(allogmutex);

	if (!DEBUG_FLAG)
		return;

	ZeroMemory(ltbuft, sizeof(wchar_t)* 80);
	ZeroMemory(ltbufBT, sizeof(wchar_t)* 4096);

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	wcsftime(ltbuft, 80, L"%d-%m-%Y %I:%M:%S \0", &timeinfo);
	wcscpy_s(ltbufBT, ltbuft);
	wcscat_s(ltbufBT, msg);

	wcout << ltbufBT;

	*file << ltbufBT;
	file->flush();


}
