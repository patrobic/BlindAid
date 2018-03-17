#pragma once

#include <vector>
#include "IParameters.h"
#include "Logger.h"

enum Type { Color = 1, Depth = 2, Both = Color + Depth };

class GlobalParameters
{
public:
  GlobalParameters(std::vector<std::string> args, std::string path)
  {
    _args = args;
    _path = path;

    Defaults();
  }

  void Defaults()
  {
    _exePath = "C:\\BlindAid";
    _logLevel = LogLevel::Warning;
    _loadFromDisk = false;
    _menuEnabled = true;
  }

  std::string GetExePath() { return _exePath; }
  void SetExePath(std::string executablePath) { _exePath = executablePath; }

  LogLevel *GetLogLevel() { return &_logLevel; }
  void SetLogLevel(LogLevel logLevel) { _logLevel = logLevel; }

  bool GetMenuEnabled() { return _menuEnabled; }
  void SetMenuEnabled(bool menuEnabled) { _menuEnabled = menuEnabled; }

  bool GetLoadFromDisk() { return _loadFromDisk; }
  void SetLoadFromDisk(bool loadFromDisk) { _loadFromDisk = loadFromDisk; }

  Type GetType() { return _type; }
  void SetType(Type type) { _type = type; }

  std::vector<std::string> _args;
  std::vector<std::string> _menuArgs;
  std::string _path;

private:
  // path of executable (used to calculate relative paths).
  std::string _exePath;

  // verbosity of logging system.
  LogLevel _logLevel;

  // activate the user interactive menu.
  bool _menuEnabled;

  // load paramaters from configuration file on disk.
  bool _loadFromDisk;

  // save color, depth, or both
  Type _type = Both;
};