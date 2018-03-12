#pragma once

#include "MenuMain.h"
#include "Config.h"

class Main
{
public:
  Main(std::vector<std::string> args);
  void Start();

private:
  void Process();
  void LoadSettings();
  void SetExePath();
  void SetWindowPosition();
  void Launcher();

  bool CheckFlag(const std::string & option, int *next = NULL);

  std::vector<std::string> _args;
  bool _bypassMenu = false;

  GlobalParameters _globalParams;
  Core::Core *_core;
  Core::Parameters _params;
  Core::Data _results;

  Configuration _config;
  Logger _logger;
  MainMenu _menu;
};