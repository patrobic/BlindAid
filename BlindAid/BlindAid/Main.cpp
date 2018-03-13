#include "Menu.h"
#include "ConfigParse.h"

#define CONFIG "\\BlindAid.cfg"

void main(int argc, char *argv[])
{
  GlobalParameters globalParams;
  Logger logger(globalParams.GetLogLevel());

  do {
    Core::Parameters params(&globalParams);

    ParseConfiguration config(&params, &logger);
    config.Configure(std::vector<std::string>(argv, argv + argc));

    if (!globalParams.GetBypassMenu())
    {
      Menu menu(&params, &logger);
      menu.ShowMenu();
    }

    Core::Data results(&params);
    Core::Core core(&params, NULL, &results, &logger);
    core();

    system("pause");
    system("cls");

    cv::destroyAllWindows();

  } while (!globalParams.GetBypassMenu());
}