#pragma once

#include <conio.h>

#include "LoadConfig.h"
#include "SaveConfig.h"

#include "MenuSimulate.h"
#include "MenuRealtime.h"

#include "..\Modules\Core.h"

class MainMenu
{
public:
  MainMenu();
  void operator()();

private:
  void Configure();
  void ShowMenu();
  void Settings();

  RealtimeMenu _realtime;
  SimulateMenu _simulate;

  Core::Core *_core;
  Core::Parameters _params;
  Core::Data _results;
};