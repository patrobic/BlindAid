#include "Modes.h"

#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

#define NAME "MODES"

Modes::Modes(Core::Parameters *params, Logger *logger) : Class(params, logger)
{

}

string categories[][3] = {
  { "COMMAND", "FLAGS", "CATEGORY" },
  { "blindaid", "-a | -c | -t <path> | -s <path> -r [delay] [path]", "mode selection" },
  { "", "-d -v [level] -l", "debugging options" },
  { "", "-p <port>", "connection settings" },
  { "", "-do {fr | hp} -tl {dl | bd}", "module selection" },
  { "", "-coloroff | -depthoff", "channel selection" },
  { "", "-?", "help" }
};

string messages[][5] = {
  { "FLAG", "[ARGUMENT]", "DESCRIPTION", "DETAILS", "CHANGES" },
  { "?", "", "Show Help", "display flag descriptions, then exit", "" },
  { "a", "", "Realtime Mode", "bypass menu, no user interaction", "Camera ON /Glove ON" },
  { "c", "", "Camera Only", "disable glove, print control to screen", "Camera ON / Glove OFF" },
  { "t", "<path>", "Glove Only", "disable camera, load images from disk", "Camera OFF/Glove ON" },
  { "s", "<path>", "Simulate Mode", "disable performance optimizations", "Camera OFF/Glove OFF" },
  { "r", "[delay] [path]", "Record Enabled", "save images to disk, 0 for manual", "Record ON" },
  { "d", "", "Display Images", "show color/depth images to screen", "Display ON" },
  { "v", "[level]", "Verbose Messages", "print info messages to screen", "Logging ON" },
  { "l", "", "Low Performance", "disable multi threading optimizations", "Threads OFF" },
  { "p", "<port #>", "Set COM Port Number", "for Bluetooth glove connection", "" },
  { "do", "{fr | hp}", "Depth Obstacle Mode", "fixed regions/hand position", "DepthObstacle FR/HP" },
  { "tl", "{dl | bd}", "Traffic Light Mode", "deep learning/blob detector", "TrafficLight DL/BD" },
  { "coloroff", "", "Depth Image Only", "disable color stream processing", "Color OFF" },
  { "depthoff", "", "Color Image Only", "disable depth stream processing", "Depth OFF" }
};

string scenarios[][4] = {
  { "COMMAND ", "FLAGS", "DESCRIPTION", "PURPOSE" },
  { "blindaid", "", "Menu Interface", "manual configuration, via interactive menu" },
  { "blindaid", "-a", "Realtime Final", "complete experience, for final product demo" }, // -a
  { "blindaid", "-c", "Capture Only", "to demo without glove, print control to screen" }, // -c
  { "blindaid", "-t path", "Control Only", "to demo without camera, load images from disk" }, // -t path (-d)
  { "blindaid", "-s path", "Simulate All", "disable camera and glove, only test software loop" }, // -s (-c -t path)
  { "blindaid", "-a -d", "Realtime w\\Debug", "full experience w\\image display, low performance" }, // -d
  { "blindaid", "-c -d", "Capture w\\Debug", "capture only w\\display, to demonstrate processing" }, // -c -d
  { "blindaid", "-r ms", "Record Images", "save images periodically, or 0 for manual trigger" }, // -r (-c -d)
};

void Modes::GetHelp()
{
  cout << "USAGE: Summary of flags by category.\n";
  for (int i = 0; i < 6; ++i)
    cout << left << "    " << setw(10) << categories[i][0] << "\t[" << setw(50) << (categories[i][1] + "]") << "\t(" << categories[i][2] << ")\n";

  cout << "\nDETAILS: Description of flags and parameters.\n";
  for (int i = 0; i < 15; ++i)
    cout << left << "    -" << setw(15) << (messages[i][0] + " " + messages[i][1]) << "\t" << setw(23) << messages[i][2] << "\t(" << setw(40) << (messages[i][3] + ")") << (messages[i][4].size() > 0 ? "\t[" + messages[i][4] + "]" : "") << "\n";

  cout << "\nSCENARIOS: Useful argument combinations.\n";
  for (int i = 0; i < 9; ++i)
    cout << left << "    " << setw(25) << (scenarios[i][0] + " " + scenarios[i][1]) << "\t" << setw(20) << scenarios[i][2] << "\t(" << scenarios[i][3] << ")\n";

  system("pause");
  exit(0);
}

void Modes::BypassMenu()
{
  _params->GetGlobalParameters()->SetBypassMenu(true);
  LOG(Warning, "'-a': Running in Realtime mode");
}

void Modes::CaptureOnly()
{
  _params->GetGlobalParameters()->SetBypassMenu(true);
  _params->GetControlParams()->SetMode(Simulate);
  LOG(Warning, "'-c': Simulating Control (messages sent to screen)");
}

void Modes::ControlOnly(vector<string> params)
{
  string path;

  if (FlagToPath(params, 0, path))
  {
    _params->GetGlobalParameters()->SetBypassMenu(true);
    _params->GetCaptureParams()->SetMode(Simulate);
    _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(path);
    _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(path);
    LOG(Warning, "'-t': Simulating Capture (images loaded from disk, path: '" + path + "')");
  }
  else
    LOG(Warning, "'-t': Invalid image path (usage: -t path)");
}

void Modes::SimulateMode(vector<string> params)
{
  string path;

  if (FlagToPath(params, 0, path))
  {
    CaptureOnly();
    ControlOnly(params);
    LOG(Warning, "'-s': Simulating All (camera and glove disabled).");
  }
  else
    LOG(Warning, "'-s': Invalid image path (usage: -s path)");
}

void Modes::EnableRecord(vector<string> params)
{
  int interval = 0;
  string path;

  if (FlagToInt(params, 0, interval))
    _params->GetRecordParams()->SetInterval(interval);

  if (FlagToString(params, 0, path) || FlagToString(params, 1, path))
    _params->GetRecordParams()->SetPath(path);

  _params->GetGlobalParameters()->SetBypassMenu(true);
  _params->GetRecordParams()->SetToggle(Enabled);

  CaptureOnly();
  EnableDisplay();
  LOG(Warning, "'-r': Enabling Record (save " + (interval > 0 ? "every " + to_string(interval) + "ms" : "on key press") + " to folder " + _params->GetRecordParams()->GetPath() + ")");
}

void Modes::EnableDisplay()
{
  _params->GetDisplayParams()->SetToggle(Enabled);
  LOG(Warning, "'-d': Enabling Display (debug images displayed on screen)");
}

void Modes::EnableVerbose(vector<string> params)
{
  int level = 0;
  if (FlagToInt(params, 0, level))
    _params->GetGlobalParameters()->SetLogLevel((LogLevel)level);

  _params->GetGlobalParameters()->SetLogLevel(LogLevel::Info);
  LOG(Warning, "'-v': Enabling Verbose (debug messages printed on screen)");
}

void Modes::LowPerformance()
{
  _params->SetMode(Simulate);
  _params->GetVisionParams()->SetMode(Simulate);
  _params->GetVisionParams()->GetDepthObstacleParams()->SetMode(Simulate);
  _params->GetVisionParams()->GetTrafficLightParams()->SetMode(Simulate);
  _params->GetDisplayParams()->SetMode(Simulate);
  LOG(Warning, "'-l': Enabling Low Performance Mode (optimizations disabled)");
}

void Modes::SetComPort(vector<string> params)
{
  int port = 0;

  if (FlagToInt(params, 0, port))
  {
    _params->GetControlParams()->GetRealtimeParams()->SetSerialPort(port);
    LOG(Warning, "'-p': Setting COM Port for Bluetooth to " + to_string(port));
  }
  else
    LOG(Warning, "Invalid COM Port (usage: -p #)");
}

void Modes::DepthObstacleMode(vector<string> params)
{
  string version;

  if (FlagToString(params, 0, version))
  {
    if (version == "fr" || version == "hp")
      if (version == "fr")
      {
        _params->GetVisionParams()->GetDepthObstacleParams()->SetVersion(Vision::DepthObstacle::Parameters::Version::FixedRegions);
        LOG(Warning, "'-do': Setting Depth Obstacle mode to Fixed Regions");
      }
      else
      {
        _params->GetVisionParams()->GetDepthObstacleParams()->SetVersion(Vision::DepthObstacle::Parameters::Version::HandPosition);
        LOG(Warning, "'-do': Setting Depth Obstacle mode to Hand Position");
      }
    else
      LOG(Warning, "Invalid Depth Obstacle Mode (usage: -s {fr | hp})");
  }
}

void Modes::TrafficLightMode(vector<string> params)
{
  string version;

  if (FlagToString(params, 0, version))
  {
    if (version == "dl" || version == "bd")
      if (version == "dl")
      {
        _params->GetVisionParams()->GetTrafficLightParams()->SetVersion(Vision::TrafficLight::Parameters::Version::DeepLearning);
        LOG(Warning, "'-tl': Setting Traffic Light Mode to Deep Learning");
      }
      else
      {
        _params->GetVisionParams()->GetTrafficLightParams()->SetVersion(Vision::TrafficLight::Parameters::Version::BlobDetector);
        LOG(Warning, "'-tl': Setting Traffic Light Mode to Blob Detector");
      }
    else
      LOG(Warning, "Invalid Traffic Light Mode (usage: -s {dl | bd})");
  }
}

void Modes::DisableColor()
{
  _params->GetGlobalParameters()->SetType(Depth);
  LOG(Warning, "'-coloroff': Disabling color image stream (depth processing only)");
}

void Modes::DisableDepth()
{
  _params->GetGlobalParameters()->SetType(Color);
  LOG(Warning, "'-depthoff': Disabling depth image stream (color processing only)");
}

bool Modes::FlagToInt(vector<string> param, int index, int &number)
{
  if (index >= param.size() || param.at(index).length() == 0)
    return false;

  if (param.at(index).find_first_not_of("0123456789") != string::npos)
    return false;

  number = atoi(param.at(index).c_str());

  return true;
}

bool Modes::FlagToString(vector<string> param, int index, string &str)
{
  if (index >= param.size() || param.at(index).length() == 0)
    return false;

  if (isdigit(param.at(index).at(0)))
    return false;

  str = param.at(index);

  return true;
}

bool Modes::FlagToPath(vector<string> param, int index, string &path)
{
  if (index >= param.size() || param.at(index).length() == 0)
    return false;

  if (!GetFileAttributesA(param.at(index).c_str()) || !FILE_ATTRIBUTE_DIRECTORY || PathIsDirectoryEmpty(param.at(index).c_str()))
    return false;

  path = param.at(index);

  return true;
}