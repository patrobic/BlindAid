#pragma once

#include "MenuSimulate.h"
#include "MenuRealtime.h"

class MainMenu : public Menu
{
public:
  MainMenu(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger, MainConfiguration *config);
  void ShowMenu();

private:
  RealtimeMenu _realtime;
  SimulateMenu _simulate;
};