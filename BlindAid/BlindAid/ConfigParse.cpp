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

  int index = 0;

  if (CheckFlag("-?"))
    _modes.HelpFlag();

  if (CheckFlag("-d"))
    _modes.DisplayFlag();

  if (CheckFlag("-v") || VERBOSE)
    _modes.VerboseFlag();

  if (CheckFlag("-a"))
    _modes.RealtimeFlag();

  if (CheckFlag("-c"))
    _modes.CaptureFlag();

  if (CheckFlag("-t", 1))
    _modes.ControlFlag(_prms);

  if (CheckFlag("-r", 1))
    _modes.RecordFlag(_prms);

  if (CheckFlag("-p", 1))
    _modes.PortFlag(_prms);

  if (CheckFlag("-coloroff"))
    _modes.ColorFlag();

  if (CheckFlag("-depthoff"))
    _modes.DepthFlag();
}

bool ParseConfiguration::CheckFlag(const std::string& option, int numParams)
{
  _prms.clear();

  for (int i = 0; i < _args.size(); ++i)
    if (_args.at(i) == option && (i + 1) < _args.size())
    {
      _index = i;

      for (int j = 1; j <= numParams && (i + j) < _args.size(); ++j)
        _prms.push_back(_args.at(i + j));

      return true;
    }

  return false;
}