#include "Logger.h"

#include <iostream>
#include <iomanip>

using namespace std;

void Logger::operator()(LogLevel level, std::string message, std::string name, std::chrono::steady_clock::time_point start, std::string subName)
{
  Log(level, message, name, start, subName, true);
}

void Logger::operator()(LogLevel level, std::string message, std::string name, std::string subName)
{
  Log(level, message, name, chrono::steady_clock::now(), subName, false);
}

void Logger::Log(LogLevel level, std::string message, std::string name, std::chrono::steady_clock::time_point start, std::string subName, bool time)
{
  if (level <= *_maxLevel)
  {
    _printMutex.lock();

    cout << "[" << setw(7) << left << _levels[level].c_str() << "] ";
    cout << "[" << setw(8) << right << name.c_str();

    if (subName.size() > 0)
      cout << "/" << setw(8) << left << subName.c_str() << "] ";
    else
      cout << setw(11) << "] ";

    cout << setw(79) << left << message.c_str();

    if (time)
      cout << " [" << setw(5) << right << (int)(chrono::duration_cast<chrono::duration<double>>(chrono::steady_clock::now() - start).count() * 1000) << "ms]";

    cout << "\n";

    _printMutex.unlock();
  }
}