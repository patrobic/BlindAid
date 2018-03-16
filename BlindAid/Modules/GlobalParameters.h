#pragma once

#include <vector>
#include "IParameters.h"
#include "Logger.h"

enum Type { Color = 1, Depth = 2, Both = Color + Depth };

class GlobalParameters
{
public:
  GlobalParameters()
  {
    Defaults();
  }

  void Defaults()
  {
    _exePath = "C:\\BlindAid";
    _logLevel = LogLevel::Warning;
    _menuEnabled = true;
  }

  std::string GetExePath() { return _exePath; }
  void SetExePath(std::string executablePath) { _exePath = executablePath; }

  LogLevel *GetLogLevel() { return &_logLevel; }
  void SetLogLevel(LogLevel logLevel) { _logLevel = logLevel; }

  bool GetMenuEnabled() { return _menuEnabled; }
  void SetMenuEnabled(bool menuEnabled) { _menuEnabled = menuEnabled; }

  Type GetType() { return _type; }
  void SetType(Type type) { _type = type; }

private:
  // path of executable (used to calculate relative paths).
  std::string _exePath;

  LogLevel _logLevel;

  bool _menuEnabled;

  // save color, depth, or both
  Type _type = Both;
};