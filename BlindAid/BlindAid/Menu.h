#pragma once

#include <conio.h>

#include "opencv2\videoio.hpp"

#include "LoadConfig.h"
#include "SaveConfig.h"

#include "..\Modules\ModuleCore.h"

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

  Data _data;

  Core _core;
  Core::Parameters _params;
  Core::Results _results;
};