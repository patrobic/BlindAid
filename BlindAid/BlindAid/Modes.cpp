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

void Modes::HelpFlag()
{
  cout << "Command line argument flags to choose operation modes:\n\
      '-a': Realtime production mode (camera and glove connected).\n\
      '-c': Camera only mode (with debug messages, glove disabled).\n\
      '-d': Debug mode (enables extra printouts and image windows).\n\
      '-v': Verbose mode (enables extra printouts, forced by debug).\n\
      '-t path': Control only mode (enter saved images folder path).\n\
      '-r #': Record mode enabled (enter interval in ms or 0 for manual).\n\
      '-p #': Set Bluetooth COM port index manually.\n\
      '-?': Help (print flags + descriptions, then exit).\n";
  // '-m': Launch user Menu
  // '-s path': Load settings from disk
  // '-bd'
  // '-dl'
  // '-hp'
  // '-fr'
  system("pause");
  exit(0);
}

void Modes::DisplayFlag()
{
  _params->GetDisplayParams()->SetToggle(Enabled);
  LOG(Warning, "'-d': Enabling display debug mode");
}

void Modes::VerboseFlag()
{
  _params->GetGlobalParameters()->SetLogLevel(LogLevel::Info);
  LOG(Warning, "'-v': Enabling verbose debug mode");
}

void Modes::RealtimeFlag()
{
  _params->GetGlobalParameters()->SetBypassMenu(true);
  LOG(Warning, "'-a': Running in Realtime mode");
}

void Modes::CaptureFlag()
{
  _params->GetControlParams()->SetMode(Simulate);
  _params->SetMode(Realtime);
  LOG(Warning, "'-c': Simulating Control to screen");
}

void Modes::ControlFlag(vector<string> params)
{
  string path;

  if (FlagToPath(params.at(0), path))
  {
    _params->GetCaptureParams()->SetMode(Simulate);
    _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Sequence);
    _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(path);
    _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(path);
    LOG(Warning, "'-t': Simulating Capture from disk (path: '" + path + "')");
  }
}

void Modes::RecordFlag(vector<string> params)
{
  int interval = 0;

  if (FlagToInt(params.at(0), interval))
    _params->GetRecordParams()->SetInterval(interval);

  _params->GetRecordParams()->SetToggle(Enabled);
  LOG(Warning, "'-r': Enabling recording to disk (" + to_string(interval) + "ms)");
}

void Modes::PortFlag(vector<string> params)
{
  int port = 0;

  if (FlagToInt(params.at(0), port))
  {
    _params->GetControlParams()->GetRealtimeParams()->SetSerialPort(port);
    LOG(Warning, "'-p': COM port set to " + to_string(port) + "");
  }
  else
    LOG(Warning, "Please enter valid COM port (usage: -p #)");
}

void Modes::ColorFlag()
{
  _params->GetGlobalParameters()->SetType(Depth);
  LOG(Warning, "'-coloroff': Disabling color stream.");
}

void Modes::DepthFlag()
{
  _params->GetGlobalParameters()->SetType(Color);
  LOG(Warning, "'-depthoff': Disabling depth stream.");
}

void Modes::SimulateFlag()
{
  _params->GetDisplayParams()->SetMode(Simulate);
  _params->GetVisionParams()->SetMode(Simulate);
  _params->GetVisionParams()->GetDepthObstacleParams()->SetMode(Simulate);
  _params->GetVisionParams()->GetTrafficLightParams()->SetMode(Simulate);
  _params->GetControlParams()->SetMode(Simulate);
  _params->GetDisplayParams()->SetMode(Simulate);
  _params->GetRecordParams()->SetMode(Simulate);
  LOG(Warning, "'-s': Setting simulation mode.");
}

bool Modes::FlagToInt(string param, int &number)
{
  if (param.find_first_not_of("0123456789") != string::npos)
    return false;

  number = atoi(param.c_str());

  return true;
}

bool Modes::FlagToString(string param, string &str)
{
  str = param;

  return true;
}

bool Modes::FlagToPath(string param, string &path)
{
  if (!GetFileAttributesA(param.c_str()) || !FILE_ATTRIBUTE_DIRECTORY || PathIsDirectoryEmpty(param.c_str()))
    return false;

  path = param;

  return true;
}