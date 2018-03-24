#include "Parse.h"

#include <windows.h>
#include <Pathcch.h>
#include <Shlwapi.h>

#include "Messages.h"

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

#ifdef _DEBUG
#define VERBOSE true
#else
#define VERBOSE false
#endif

#define NAME "CONFIG"

Parse::Parse(Core::Parameters *params, Logger *logger) : Class(params, logger),
_modes(params, logger)
{

}

void Parse::Configure()
{
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

  if (CheckFlag("-cc", 1))
    _modes.SetConsecutiveCount(_prms);

  if (CheckFlag("-do", 1))
    _modes.DepthObstacleMode(_prms);

  if (CheckFlag("-tl", 1))
    _modes.TrafficLightMode(_prms);

  if (CheckFlag("-coloroff"))
    _modes.DisableColor();

  if (CheckFlag("-depthoff"))
    _modes.DisableDepth();

  if (CheckFlag("-smooth", 1))
    _modes.SetDepthFrameSmoothing(_prms);

  if (CheckFlag("-conf", 1))
    _modes.SetConfidence(_prms);

  if (CheckFlag("-region", 2))
    _modes.SetRegion(_prms);

  if (CheckFlag("-ignore", 1))
    _modes.SetPercentileToIgnore(_prms);

  if (CheckFlag("-valid", 1))
    _modes.SetValidRatioThreshold(_prms);

  if (CheckFlag("-delta", 1))
    _modes.DeltaToIgnore(_prms);
}

bool Parse::CheckFlag(const std::string& option, int numParams)
{
  _prms.clear();

  for (int i = 0; i < _params->GetGlobalParameters()->_args.size(); ++i)
    if (_params->GetGlobalParameters()->_args.at(i) == option)
    {
      _index = i;

      for (int j = 1; j <= numParams && (i + j) < _params->GetGlobalParameters()->_args.size(); ++j)
        if (_params->GetGlobalParameters()->_args.at(i + j)[0] != '-')
          _prms.push_back(_params->GetGlobalParameters()->_args.at(i + j));
        else
          break;

      return true;
    }

  return false;
}