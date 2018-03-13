#include "ConfigMain.h"

MainConfiguration::MainConfiguration(Core::Parameters *params, Logger *logger) : Configuration(params, logger),
  _saveConfig(params, logger),
  _loadConfig(params, logger),
  _parseConfig(params, logger)
{

}

void MainConfiguration::Configure(std::vector<std::string> args)
{
  _parseConfig.Configure(args);
}

void MainConfiguration::Configure(std::string file)
{
  // TODO: implement proper file loading/validating mechanics that creates new file if nonexistant or invalid.
  // if(file exists)
  //    try(LoadConfiguration());
  //    if(!file.valid) .. LoadConfig should return if the file is valid (contains all values, and sensical)
  //      if(PromptOverwrite()) ... prompt user to overwrite existing corrupt file?
  //        Saveconfiguration();
  //      else
  //        throw exception(); ... terminate application!
  // else ... no configuration exists at all (new installation).
  //    SaveConfiguration(); ... create a file by saving the default configuration specified in each class's Parameters class.

  if (std::ifstream(file))
    _saveConfig.Configure(file);

  _loadConfig.Configure(file);
}