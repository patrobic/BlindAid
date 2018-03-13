#pragma once

#include "MenuMain.h"
#include "Config.h"

class Launcher : public Menu
{
public:
  Launcher(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger);
  void ShowMenu();

private:
  void Process();
  void LoadSettings();
  void SetExePath();
  void SetWindowPosition();

  MainMenu _menu;
};