#pragma once

#include "Class.h"
#include "Modes.h"

class Menu : public Class
{
public:
  Menu(Core::Parameters *params, Logger *logger);
  bool ShowMenu();

private:
  bool RealtimeMenu();
  bool SimulateMenu();

  Modes _modes;
  };