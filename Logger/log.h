#pragma once

#include <cstdarg>
#include <ctime>
#include <memory>
#include <iostream>
#include <fstream>

class Log
{
public:
	Log() = default;
	Log(const Log&) = default;
	Log(Log&&) = default;
	~Log() = default;
	Log& operator=(const Log&) = default;

	void log(int level, int line, std::string from, const char* format, ...);

	static const int LOG_SUCCESS;
	static const int LOG_INFO;
	static const int LOG_WARNING;
	static const int LOG_ERROR;
	static const int LOG_CRITICAL;
	
private:
	static const int LOG_UNKNOWN;

	static std::string getLevel(int level);
	std::ofstream* file;
};

extern std::shared_ptr<Log> logger;

#define LOG_SUCCESS(...) logger->log(Log::LOG_SUCCESS, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) logger->log(Log::LOG_INFO, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) logger->log(Log::LOG_WARNING, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) logger->log(Log::LOG_ERROR, __LINE__, __VA_ARGS__)
#define LOG_CRITICAL(...) logger->log(Log::LOG_CRITICAL, __LINE__, __VA_ARGS__)