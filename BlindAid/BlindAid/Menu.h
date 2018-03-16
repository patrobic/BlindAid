#pragma once

#include "Class.h"
#include "Modes.h"

class Menu : public Class
{
public:
  Menu(Core::Parameters *params, Logger *logger);
  void ShowMenu();

private:
  void RealtimeMenu();
  void SimulateMenu();
  std::string RequestUserFlag(std::string message);

  Modes _modes;
};