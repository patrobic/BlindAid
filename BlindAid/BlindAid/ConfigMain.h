#pragma once

#include "Config.h"

#include "ConfigLoad.h"
#include "ConfigSave.h"
#include "ConfigParse.h"

class MainConfiguration : public Configuration
{
public:
  MainConfiguration(Core::Parameters *params, Logger *logger);
  void Configure(std::vector<std::string> args);
  void Configure(std::string file);

private:
  SaveConfiguration _saveConfig;
  LoadConfiguration _loadConfig;
  ParseConfiguration _parseConfig;
};