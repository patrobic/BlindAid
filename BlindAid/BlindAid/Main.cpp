#include <Windows.h>

#include "Menu.h"
#include "Config.h"

#define CONFIG "\\BlindAid.cfg"
#define NAME "MAIN"

void main(int argc, char *argv[])
{
  GlobalParameters globalParams(std::vector<std::string>(argv, argv + argc), CONFIG);
  Logger logger(globalParams.GetLogLevel());

  while (true)
  {
    try
    {
      // create parameters and config objects
      Core::Parameters params(&globalParams);

      // load/parse configuration
      Configuration config(&params, &logger);
      config.Configure();

      // create core objects
      Core::Data results(&params);
      Core::Core core(&params, NULL, &results, &logger);

      // execute core processing
      core();
    }
    catch (std::exception e)
    {
      logger(Warning, e.what(), "MAIN");
    }
  }
}