#pragma once

#include <iostream>
#include <conio.h>
#include <exception>

#include "..\Modules\Core.h"
#include "..\Modules\Logger.h"

class Class
{
public:
  Class(Core::Parameters *params, Logger *logger)
  {
    _params = params;
    _logger = logger;
  }

protected:
  Core::Parameters *_params;
  Logger *_logger;
};