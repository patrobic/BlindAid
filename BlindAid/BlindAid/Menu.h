#pragma once

#include <conio.h>

#include "LoadConfig.h"
#include "SaveConfig.h"

#include "..\Modules\Core.h"

class MainMenu
{
public:

  MainMenu();
  void operator()();

private:
  void Realtime();
  void Simulate();
  void Settings();

  void LoadFile(Capture::Parameters::MediaType mode, std::string depthPath);

  void TestVideo(std::string colorVideoPath, std::string depthPath, int count);
  void TestPhoto(std::string colorPath, std::string depthPath, int count);

  void TestRealtimeCapture();
  void TestRealtimeControl(std::string colorPath, std::string depthPath, int count);

  Core::Core _core;
  Core::Parameters _params;
  Core::Data _results;
};