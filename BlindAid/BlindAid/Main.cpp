#include "Launcher.h"
#include "ConfigMain.h"

#define CONFIG_FILE "BlindAid.cfg"

void main(int argc, char *argv[])
{
  std::vector<std::string> args(argv, argv + argc);

  GlobalParameters _globalParams;
  Core::Core *_core = NULL; // the creation of this depends on parameters.
  Core::Parameters _params(&_globalParams);
  Core::Data _results(&_params);
  Logger _logger(_globalParams.GetLogLevel());

  MainConfiguration config(&_params, &_logger);
  config.Configure(args);

  Launcher launcher(_core, &_params, &_results, &_logger);
  launcher.ShowMenu();

  system("pause");

  return;
}