#pragma once

#include <conio.h>

#include "MenuSimulate.h"
#include "MenuRealtime.h"
#include "Config.h"

#include "..\Modules\Core.h"

class MainMenu
{
public:
  MainMenu();
  void operator()();
  Core::Parameters *GetParameters() { return _params; }

private:
  void Setup();
  void Process();
  void ShowMenu();
  void LoadSettings();

  RealtimeMenu _realtime;
  SimulateMenu _simulate;

  Configuration _configuration;

  Core::Core *_core;
  Core::Parameters _params;
  Core::Data _results;

  std::string _exePath;
};