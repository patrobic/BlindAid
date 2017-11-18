#pragma once

#include "..\Modules\Core.h"

class RealtimeMenu
{
public:
  RealtimeMenu(Core::Core *core, Core::Parameters *params, Core::Data *data);
  void operator()();
  void ShowMenu();
  void Process();

private:
  void TestRealtimeCapture();
  void TestRealtimeControl(std::string colorPath, std::string depthPath, int count);

  Core::Core *_core;
  Core::Parameters *_params;
  Core::Data *_results;
};