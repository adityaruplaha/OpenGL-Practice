#include <sstream>
#include <Windows.h>

#include "log.h"

int Log::LOG_SUCCESS = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
int Log::LOG_INFO = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
int Log::LOG_WARNING = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
int Log::LOG_ERROR = FOREGROUND_RED | FOREGROUND_INTENSITY;

Log::Log(std::string filename)
{
	file.open(filename, std::ofstream::out | std::ofstream::trunc);
}

Log::~Log()
{
	file.close();
}

void Log::log(int level, const char* format, ...)
{
	// get time
	time_t rawtime;
	time(&rawtime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	char time_buf[64];
	strftime(time_buf, sizeof(time_buf) / sizeof(char), "[%D %I:%M%p] ", &timeinfo);

	// generate log
	va_list args;
	va_start(args, format);


	char buf[256];
	vsprintf_s(buf, format, args);

	va_end(args);
	// 

	std::stringstream ss;
	ss << time_buf << buf;
	auto str = ss.str();

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, level);

	std::cout << str << "\n";
	file << str << "\n";
}