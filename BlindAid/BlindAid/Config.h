#pragma once

#include "..\Modules\IParameters.h"
#include "..\Modules\Core.h"

class Configuration
{
public:
  Configuration(Core::Parameters *params, Logger *logger)
  {
    _params = params;
    _logger = logger;
  }
  
  void Configure();

protected:
  Core::Parameters *_params;
  Logger *_logger;
};