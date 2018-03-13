#include "ConfigParse.h"

#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

#ifdef _DEBUG
#define VERBOSE true
#else
#define VERBOSE false
#endif

#define NAME "CONFIG"

ParseConfiguration::ParseConfiguration(Core::Parameters *params, Logger *logger) : Configuration(params, logger)
{

}

void ParseConfiguration::Configure(vector<string> args)
{
  _args = args;

  HelpFlag();
  DisplayFlag();
  VerboseFlag();
  RealtimeFlag();
  CaptureFlag();
  ControlFlag();
  RecordFlag();
  PortFlag();
  ColorFlag();
  DepthFlag();
}

void ParseConfiguration::HelpFlag()
{
  if (CheckFlag("-?"))
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

    system("pause");
    exit(0);
  }
}

void ParseConfiguration::DisplayFlag()
{
  if (CheckFlag("-d"))
  {
    _params->GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
    LOG(Warning, "'-d': Enabling display debug mode");
  }
}

void ParseConfiguration::VerboseFlag()
{
  if (CheckFlag("-v") || VERBOSE)
  {
    _params->GetGlobalParameters()->SetLogLevel(LogLevel::Info);
    LOG(Warning, "'-v': Enabling verbose debug mode");
  }
}

void ParseConfiguration::RealtimeFlag()
{
  if (CheckFlag("-a"))
  {
    _params->GetGlobalParameters()->SetBypassMenu(true);
    LOG(Warning, "'-a': Running in Realtime mode");
  }
}

void ParseConfiguration::CaptureFlag()
{
  if (CheckFlag("-c"))
  {
    _params->GetGlobalParameters()->SetBypassMenu(true);
    _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
    _params->SetMode(SwitchableParameters::Mode::Realtime);
    LOG(Warning, "'-c': Simulating Control to screen");
  }
}

void ParseConfiguration::ControlFlag()
{
  int index = 0;
  if (CheckFlag("-t", &index))
  {
    string path;
    if (FlagToPath(index, &path))
    {
      _params->GetGlobalParameters()->SetBypassMenu(true);
      _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
      _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Sequence);
      _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(path);
      _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(path);
      LOG(Warning, "'-t': Simulating Capture from disk (path: '" + path + "')");
    }
    else
      LOG(Warning, "Please enter valid folder path (usage: -t C:\\Folder)");
  }
}

void ParseConfiguration::RecordFlag()
{
  int interval = 0;
  if (CheckFlag("-r", &interval))
  {
    if (FlagToInt(interval, &interval))
      _params->GetRecordParams()->SetInterval(interval);
    _params->GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
    LOG(Warning, "'-r': Enabling recording to disk (" + to_string(interval) + "ms)");
  }
}

void ParseConfiguration::PortFlag()
{
  int port = 0;
  if (CheckFlag("-p", &port))
  {
    if (FlagToInt(port, &port))
    {
      _params->GetControlParams()->GetRealtimeParams()->SetSerialPort(port);
      LOG(Warning, "'-p': COM port set to " + to_string(port) + "");
    }
    else
      LOG(Warning, "Please enter valid COM port (usage: -p #)");
  }
}

void ParseConfiguration::ColorFlag()
{
  if (CheckFlag("-coloroff"))
  {
    _params->GetCaptureParams()->SetType(SwitchableParameters::Type::Depth);
    _params->GetVisionParams()->SetType(SwitchableParameters::Type::Depth);
    _params->GetControlParams()->SetType(SwitchableParameters::Type::Depth);
    _params->GetDisplayParams()->SetType(SwitchableParameters::Type::Depth);
    _params->GetRecordParams()->SetType(SwitchableParameters::Type::Depth);
    LOG(Warning, "'-coloroff': Disabling color stream.\n");
  }
}

void ParseConfiguration::DepthFlag()
{
  if (CheckFlag("-depthoff"))
  {
    _params->GetCaptureParams()->SetType(SwitchableParameters::Type::Color);
    _params->GetVisionParams()->SetType(SwitchableParameters::Type::Color);
    _params->GetControlParams()->SetType(SwitchableParameters::Type::Color);
    _params->GetDisplayParams()->SetType(SwitchableParameters::Type::Color);
    _params->GetRecordParams()->SetType(SwitchableParameters::Type::Color);
    LOG(Warning, "'-depthoff': Disabling depth stream.\n");
  }
}

bool ParseConfiguration::CheckFlag(const std::string& option, int *next)
{
  for (int i = 0; i < _args.size(); ++i)
    if (_args.at(i) == option)
    {
      if (next != NULL && (i + 1) < _args.size())
        *next = i + 1;
      return true;
    }

  return false;
}

bool ParseConfiguration::FlagToInt(int index, int *value)
{
  if (index == 0)
    return false;

  if (_args.at(index).find_first_not_of("0123456789") != string::npos)
    return false;

  *value = atoi(_args.at(index).c_str());
  return true;
}

bool ParseConfiguration::FlagToPath(int index, std::string *value)
{
  if (index == 0)
    return false;

  *value = _args.at(index).c_str();

  DWORD ftyp = GetFileAttributesA(value->c_str());

  if (!ftyp || !FILE_ATTRIBUTE_DIRECTORY)
    return false;

  if (PathIsDirectoryEmpty(value->c_str()))
    return false;

  return true;
}