#include "Launcher.h"
#include "ConfigMain.h"

#define CONFIGFILE "BlindAid.cfg"

void main(int argc, char *argv[])
{
  GlobalParameters globalParams;
  Core::Core *core = NULL; // the creation of this depends on parameters.
  Core::Parameters params(&globalParams);
  Core::Data results(&params);
  Logger logger(globalParams.GetLogLevel());
  MainConfiguration config(&params, &logger);
  Launcher launcher(core, &params, &results, &logger, &config, std::vector<std::string>(argv, argv + argc));

  launcher.ShowMenu();

  system("pause");
}