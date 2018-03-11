#pragma once

#include "..\Modules\Core.h"

class RealtimeMenu
{
public:
  RealtimeMenu(Core::Core *core, Core::Parameters *params, Core::Data *data);
  void operator()();
  void Process();

private:
  void ShowMenu();

  void TestRealtimeComplete();
  void TestRealtimeCapture();
  void TestRealtimeControl(std::string colorPath, std::string depthPath, int count);
  void TestRecord(std::string path);

  Core::Core *_core;
  Core::Parameters *_params;
  Core::Data *_results;
};