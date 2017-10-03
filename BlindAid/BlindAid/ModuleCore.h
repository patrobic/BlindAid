#pragma once

#include "ModuleCapture.h"
#include "ModuleVision.h"
#include "ModuleControl.h"
#include "ModuleDisplay.h"

#include "SimulateCapture.h"
#include "SimulateControl.h"

class Core : public IModule
{
public:
  void Init(Data *data);
  void operator()();

private:
  IModule *_capture;
  Vision _vision;
  IModule *_control;
  Display _display;
};