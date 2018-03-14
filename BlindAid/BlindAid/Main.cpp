#include "Menu.h"
#include "Config.h"

#define CONFIG "\\BlindAid.cfg"

void main(int argc, char *argv[])
{
  GlobalParameters globalParams;
  Logger logger(globalParams.GetLogLevel());

  do {
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

    system("pause");
    system("cls");
    cv::destroyAllWindows();
  } while (!globalParams.GetBypassMenu());
}