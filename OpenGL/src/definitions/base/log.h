#pragma once

#include <cstdarg>
#include <memory>
#include <fstream>

class Log
{
public:
	Log(std::string filename)
	{		
		file.open(filename, std::ofstream::out | std::ofstream::trunc);
	}

	~Log()
	{
		file.close();
	}

	Log(const Log&) = default;
	Log(Log&&) = default;
	Log& operator=(const Log&) = default;

	void log(const char* format,  ...)
	{
		va_list args;
		va_start(args, format);
		vprintf_s(format, args);

		char buf[256];
		vsprintf_s(buf, format, args);
		this->file << buf;
		va_end(args);
	}

private:
	std::ofstream file;
};