#include <sstream>
#include <Windows.h>

#include "log.h"

const int Log::LOG_SUCCESS = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Log::LOG_INFO = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int Log::LOG_WARNING = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Log::LOG_ERROR = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int Log::LOG_CRITICAL = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

const int Log::LOG_UNKNOWN = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

void Log::log(int level, int line, std::string from, const char* format, ...)
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
	char buf[512];
	vsprintf_s(buf, format, args);
	va_end(args);
	// end generate log

	auto lv = getLevel(level);

	char ss[1024];
	sprintf_s(ss, "%s <%s>\t(%s:%i)\t%s", std::string(time_buf).c_str(), lv.c_str(), from.c_str(), line, std::string(buf).c_str());

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (lv == "<Unknown> " ? LOG_UNKNOWN : level));

	std::cout << ss << "\n";
	if (level == LOG_CRITICAL)
	{
		throw ss;
	}
}

std::string Log::getLevel(int level)
{
	switch (level)
	{
	case(LOG_CRITICAL):
		return "Critical";
	case(LOG_ERROR):
		return "Error";
	case(LOG_WARNING):
		return "Warning";
	case(LOG_INFO):
		return "Info";
	case(LOG_SUCCESS):
		return "Success";
	default:
		return "Unknown";
	}
}

extern std::shared_ptr<Log> logger = std::make_shared<Log>(Log());