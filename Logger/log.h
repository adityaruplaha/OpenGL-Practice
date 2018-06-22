#pragma once

#include <cstdarg>
#include <ctime>
#include <memory>
#include <iostream>
#include <fstream>

class Log
{
public:
	Log(std::string filename);
	Log(const Log&) = default;
	Log(Log&&) = default;
	~Log();
	Log& operator=(const Log&) = default;

	void log(int level, const char* format, ...);

	static const int LOG_SUCCESS;
	static const int LOG_INFO;
	static const int LOG_WARNING;
	static const int LOG_ERROR;
	static const int LOG_CRITICAL;

	static std::string getLevel(int level);
	
private:
	static const int LOG_UNKNOWN;

	std::ofstream file;
};