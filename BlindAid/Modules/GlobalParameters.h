#pragma once

#include "IParameters.h"
#include "Logger.h"

class GlobalParameters
{
public:
  GlobalParameters() { Defaults(); }

  void Defaults()
  {
    _exePath = "C:\\Projects\\BlindAid\\";
    _logLevel = LogLevel::Warning;
    _bypassMenu = false;
  }

  std::string GetExePath() { return _exePath; }
  void SetExePath(std::string executablePath) { _exePath = executablePath; }

  LogLevel *GetLogLevel() { return &_logLevel; }
  void SetLogLevel(LogLevel logLevel) { _logLevel = logLevel; }

  bool GetBypassMenu() { return _bypassMenu; }
  void SetBypassMenu(bool bypassMenu) { _bypassMenu = bypassMenu; }

private:
  // path of executable (used to calculate relative paths).
  std::string _exePath;

  LogLevel _logLevel;

  bool _bypassMenu;
};