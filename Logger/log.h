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

	static int LOG_SUCCESS;
	static int LOG_INFO;
	static int LOG_WARNING;
	static int LOG_ERROR;

private:
	std::ofstream file;
};