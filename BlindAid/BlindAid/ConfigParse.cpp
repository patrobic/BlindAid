#include "ConfigParse.h"

using namespace std;

#ifdef _DEBUG
#define VERBOSE true
#else
#define VERBOSE false
#endif

#define NAME "CONFIG"

ParseConfiguration::ParseConfiguration(Core::Parameters *params, Logger *logger) : Class(params, logger),
_modes(params, logger)
{

}

void ParseConfiguration::Configure(std::vector<std::string> args)
{
  _args = args;

  if (CheckFlag("-?"))
    _modes.GetHelp();

  if (CheckFlag("-c") || CheckFlag("-t") || CheckFlag("-s") || CheckFlag("-r"))
    _modes.BypassMenu();

  if (CheckFlag("-a"))
    _modes.BypassMenu();

  if (CheckFlag("-c"))
    _modes.CaptureOnly();

  if (CheckFlag("-t", 1))
    _modes.ControlOnly(_prms);

  if (CheckFlag("-s", 1))
    _modes.SimulateMode(_prms);

  if (CheckFlag("-r", 2))
    _modes.EnableRecord(_prms);

  if (CheckFlag("-d"))
    _modes.EnableDisplay();

  if (CheckFlag("-v", 1) || VERBOSE)
    _modes.EnableVerbose(_prms);

  if (CheckFlag("-l", 1) || VERBOSE)
    _modes.LowPerformance();

  if (CheckFlag("-p", 1))
    _modes.SetComPort(_prms);

  if (CheckFlag("-do", 1))
    _modes.DepthObstacleMode(_prms);

  if (CheckFlag("-tl", 1))
    _modes.TrafficLightMode(_prms);

  if (CheckFlag("-coloroff"))
    _modes.DisableColor();

  if (CheckFlag("-depthoff"))
    _modes.DisableDepth();
}

bool ParseConfiguration::CheckFlag(const std::string& option, int numParams)
{
  _prms.clear();

  for (int i = 0; i < _args.size(); ++i)
    if (_args.at(i) == option)
    {
      _index = i;

      for (int j = 1; j <= numParams && (i + j) < _args.size(); ++j)
        if (_args.at(i + j)[0] != '-')
          _prms.push_back(_args.at(i + j));
        else
          break;

      return true;
    }

  return false;
}