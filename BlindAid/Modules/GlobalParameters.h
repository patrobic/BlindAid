#pragma once

#include <vector>
#include "IParameters.h"
#include "Logger.h"

enum Type { Color, Depth, Both };

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
    _bypassMenu = false;
  }

  std::string GetExePath() { return _exePath; }
  void SetExePath(std::string executablePath) { _exePath = executablePath; }

  LogLevel *GetLogLevel() { return &_logLevel; }
  void SetLogLevel(LogLevel logLevel) { _logLevel = logLevel; }

  bool GetBypassMenu() { return _bypassMenu; }
  void SetBypassMenu(bool bypassMenu) { _bypassMenu = bypassMenu; }

  Type GetType() { return _type; }
  void SetType(Type type) { _type = type; }

private:
  // path of executable (used to calculate relative paths).
  std::string _exePath;

  LogLevel _logLevel;

  bool _bypassMenu;

  // save color, depth, or both
  Type _type = Both;
};