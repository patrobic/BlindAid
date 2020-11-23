#pragma once

#include <iostream>
#include <conio.h>
#include <exception>

#include "..\..\BlindAid.Modules\Modules\Core.h"
#include "VisionParameters.h"
#include "CoreParameters.h"
#include "..\..\BlindAid.Modules\Modules\Logger.h"

class Class
{
public:
  Class(Core::CoreParameters *params, Tools::Logger *logger)
  {
    _params = params;
    _logger = logger;
  }

protected:
  Core::CoreParameters*_params;
  Tools::Logger *_logger;
};