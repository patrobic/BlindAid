#pragma once

#include "..\Modules\Core.h"

#include "ConfigLoad.h"
#include "ConfigSave.h"

#define CONFIG_FILE "BlindAid.cfg"

class Configuration
{
public:
  Configuration(Core::Parameters *params);
  void Configure();

private:
  SaveConfiguration _saveConfig;
  LoadConfiguration _loadConfig;
};