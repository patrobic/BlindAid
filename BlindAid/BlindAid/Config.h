#pragma once

#include "Class.h"

#include "ConfigLoad.h"
#include "ConfigSave.h"
#include "ConfigParse.h"

class Configuration : public Class
{
public:
  Configuration(Core::Parameters *params, Logger *logger);
  void Configure(std::vector<std::string> args, std::string path);

private:
  void ParseArguments();
  void LoadFromDisk();

  void Initialize();
  void SetExePath();
  void SetWindowPosition();

  SaveConfiguration _saveConfig;
  LoadConfiguration _loadConfig;
  ParseConfiguration _parseConfig;

  std::vector<std::string> _args;
  std::string _path;
};