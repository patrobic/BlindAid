#include "Logger.h"

#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

namespace Tools
{
    void Logger::operator()(LogLevel level, string message, string name, steady_clock::time_point start, string subName)
    {
        Log(level, message, name, start, subName, true);
    }

    void Logger::operator()(LogLevel level, string message, string name, string subName)
    {
        Log(level, message, name, steady_clock::now(), subName, false);
    }

    void Logger::Log(LogLevel level, string message, string name, steady_clock::time_point start, string subName, bool time)
    {
        if (level <= *_maxLevel)
        {
            duration<double> dur = duration_cast<duration<double>>(steady_clock::now() - start);
            stringstream ss;

            ss.clear();
            ss << "[" << setw(7) << left << _levels[level].c_str() << "] ";
            ss << "[" << setw(8) << right << name.c_str();

            if (subName.size() > 0)
                ss << "/" << setw(8) << left << subName.c_str() << "] ";
            else
                ss << setw(11) << "] ";

            ss << setw(79) << left << message.c_str();

            if (time)
                ss << " [" << setw(5) << right << (int)(dur.count() * 1000) << "ms]";

            ss << "\n";

            _printMutex.lock();
            cout << ss.str();
            _printMutex.unlock();
        }
    }
}