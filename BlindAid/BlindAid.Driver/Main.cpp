#include <Windows.h>

#include "Menu.h"
#include "Config.h"

#define CONFIG "\\BlindAid.cfg"
#define NAME "MAIN"

void main(int argc, char *argv[])
{
  GlobalParameters globalParams(std::vector<std::string>(argv, argv + argc), CONFIG);
  Tools::Logger logger(globalParams.GetLogLevel());

  while (true)
  {
    try
    {
      Core::CoreParameters params(&globalParams);
      Configuration config(&params, &logger);
      config.Configure();

      Core::CoreData results(&params);
      Core::Core core(&params, NULL, &results, &logger);
      core();
    }
    catch (std::exception e)
    {
      system("cls");
      logger(Tools::Warning, e.what(), "MAIN");
    }
  }
}