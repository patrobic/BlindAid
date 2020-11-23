#pragma once

#include <mutex>
#include <chrono>
#include <sstream>
#include <ostream>

namespace Tools
{
	enum LogLevel { Error, Warning, Info, Test };

#pragma warning(disable : 4003)
#pragma warning(disable : 4005)
#pragma warning(disable : 4275)

#define ID(x) x
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define LOG(...) ID(GET_MACRO(__VA_ARGS__, LOG4, LOG3, LOG2)(__VA_ARGS__))

#define LOG2(LEVEL, MESSAGE) (*_logger)(LEVEL, MESSAGE, NAME);
#define LOG3(LEVEL, MESSAGE, PARAM3) (*_logger)(LEVEL, MESSAGE, NAME, PARAM3);
#define LOG4(LEVEL, MESSAGE, SUBNAME, TIME) (*_logger)(LEVEL, MESSAGE, NAME, TIME, SUBNAME);

	class Logger
	{
	public:
		Logger(std::ostream* stream, LogLevel* maxLevel)
		{
			_stream = stream;
			_maxLevel = maxLevel;
		}

		void operator()(LogLevel level, std::string message, std::string name, std::chrono::steady_clock::time_point time, std::string subName = "");
		void operator()(LogLevel level, std::string message, std::string name, std::string subName = "");

	private:
		void Log(LogLevel level, std::string message, std::string name, std::chrono::steady_clock::time_point start, std::string subName, bool time);

		std::ostream* _stream;

		LogLevel* _maxLevel;

		std::mutex _printMutex;

		std::string _levels[4] = { "ERROR", "WARNING", "INFO", "TEST" };
	};
}