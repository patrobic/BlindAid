#include "Modes.h"

#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>

#include "Messages.h"

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

#define NAME "MODES"

Modes::Modes(Core::Parameters *params, Logger *logger) : Class(params, logger)
{

}

void Modes::GetHelp()
{
  system("cls");

  cout << "CONFIGURATION MODES: BlindAid can be launched and configured in 3 ways.\n\
    Arguments: Launch from command line, configured with no interaction by passing arguments.\n\
    User Menu: Launch without arguments, configured through a user interactive menu interface.\n\
    Shortcuts: To simplify mode selection, create desktop shortcuts with argument combinations.\n\n";

  cout << "USAGE: Summary of flags by category.\n";
  for (int i = 0; i < 6; ++i)
    cout << left << "    " << setw(10) << Messages::categories[i][0] << "\t[" << setw(50) << (Messages::categories[i][1] + "]") << "\t(" << Messages::categories[i][2] << ")\n";

  cout << "\nDETAILS: Description of flags and parameters.\n";
  for (int i = 0; i < 16; ++i)
    cout << left << "    -" << setw(15) << (Messages::messages[i][0] + " " + Messages::messages[i][1]) << "\t" << setw(23) << Messages::messages[i][2] << "\t(" << setw(40) << (Messages::messages[i][3] + ")") << (Messages::messages[i][4].size() > 0 ? "\t[" + Messages::messages[i][4] + "]" : "") << "\n";

  cout << "\nSCENARIOS: Useful argument combinations.\n";
  for (int i = 0; i < 9; ++i)
    cout << left << "    " << setw(25) << (Messages::scenarios[i][0] + " " + Messages::scenarios[i][1]) << "\t" << setw(20) << Messages::scenarios[i][2] << "\t(" << Messages::scenarios[i][3] << ")\n";

  system("pause");
}

void Modes::BypassMenu()
{
  _params->GetGlobalParameters()->SetMenuEnabled(false);
  LOG(Warning, "'-a': Running in Realtime mode");
}

void Modes::CaptureOnly()
{
  _params->GetControlParams()->SetMode(Simulate);
  LOG(Warning, "'-c': Simulating Control (messages sent to screen)");
}

void Modes::ControlOnly(vector<string> params)
{
  string path;

  if (FlagToPath(params, 0, path))
  {
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
    _params->GetControlParams()->SetMode(Simulate);
    _params->GetCaptureParams()->SetMode(Simulate);
    _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(path);
    _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(path);
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

void Modes::SetConsecutiveCount(vector<string> params)
{
  int consecutiveCount = 0;

  if (FlagToInt(params, 0, consecutiveCount))
  {
    _params->GetVisionParams()->GetDepthObstacleParams()->SetConsecutiveCount(consecutiveCount);
    _params->GetVisionParams()->GetTrafficLightParams()->SetConsecutiveCount(consecutiveCount);
    LOG(Warning, "'-cc': Setting Consecutive Count to " + to_string(consecutiveCount));
  }
  else
    LOG(Warning, "Invalid Consecutive Count Value (usage: -cc {count})");
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