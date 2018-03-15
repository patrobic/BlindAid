#include "Menu.h"
#include "Config.h"

#define CONFIG "\\BlindAid.cfg"
#define NAME "MAIN"

void main(int argc, char *argv[])
{
  GlobalParameters globalParams;
  Logger logger(globalParams.GetLogLevel());

  while (true)
  {
    try
    {
      Core::Parameters params(&globalParams);
      Configuration config(&params, &logger);
      config.Configure(std::vector<std::string>(argv, argv + argc), CONFIG);

      if (!globalParams.GetBypassMenu())
      {
        Menu menu(&params, &logger);
        menu.ShowMenu();
      }

      Core::Data results(&params);
      Core::Core core(&params, NULL, &results, &logger);

      core();
    }
    catch (std::exception e)
    {
      logger(Warning, e.what(), "MAIN");
    }
  }
}