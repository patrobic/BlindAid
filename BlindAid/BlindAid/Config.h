#pragma once

#include <string>
#include <fstream>

#include "Class.h"
#include "Menu.h"
#include "Load.h"
#include "Save.h"
#include "Parse.h"

class Configuration : public Class
{
public:
  Configuration(Core::Parameters *params, Logger *logger);
  void Configure();

private:
  void ParseArguments();
  void LoadFromMenu();
  void ParseMenuArguments();
  void LoadFromDisk();

  void Initialize();
  void SetExePath();
  void SetWindowPosition();

  Menu _menu;
  Save _save;
  Load _load;
  Parse _parse;
};