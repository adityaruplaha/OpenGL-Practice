#include <sstream>
#include <Windows.h>

#include "log.h"

const int Log::LOG_SUCCESS = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Log::LOG_INFO = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int Log::LOG_WARNING = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Log::LOG_ERROR = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int Log::LOG_CRITICAL = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

const int Log::LOG_UNKNOWN = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

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

	auto lv = getLevel(level);

	std::stringstream ss;
	ss << time_buf << lv << buf;
	auto str = ss.str();

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (lv == "<Unknown> " ? LOG_UNKNOWN : level));

	std::cout << str << "\n";
	file << str << "\n";
}

std::string Log::getLevel(int level)
{
	switch (level)
	{
	case(LOG_CRITICAL):
		return "<Critical> ";
	case(LOG_ERROR):
		return "<Error> ";
	case(LOG_WARNING):
		return "<Warning> ";
	case(LOG_INFO):
		return "<Info> ";
	case(LOG_SUCCESS):
		return "<Success> ";
	default:
		return "<Unknown> ";
	}
}