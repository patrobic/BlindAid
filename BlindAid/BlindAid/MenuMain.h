#pragma once

#include "Menu.h"
#include "MenuSimulate.h"
#include "MenuRealtime.h"

class MainMenu : public Menu
{
public:
  MainMenu(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger);
  void ShowMenu();

private:
  RealtimeMenu _realtime;
  SimulateMenu _simulate;
};