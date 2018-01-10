#pragma once

#include <array>

#include "opencv2\core.hpp"
#include "IParameters.h"

class IData
{
public:
  virtual bool Valid() = 0;
  virtual void Clear() = 0;
  // TODO: check that parameters are valid in all Modules.
  // virtual bool Valid() = 0;

  int GetStatus() { return _status; }
  void SetStatus(bool status) { _status = status; }

protected:
  bool _status = true;

};