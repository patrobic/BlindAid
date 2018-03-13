#pragma once

#include "MenuMain.h"
#include "ConfigMain.h"

class Launcher : public Menu
{
public:
  Launcher(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger, MainConfiguration *config, std::vector<std::string> args);
  void ShowMenu();

private:
  void Process();
  void LoadSettings();
  void SetExePath();
  void SetWindowPosition();

  MainMenu _menu;

  std::vector<std::string> _args;
};