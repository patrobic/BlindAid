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

  bool GetStatus() { return _status; }
  void SetStatus(bool status) { _status = status; }

  bool GetStop() { return _stop; }
  void SetStop(bool stop) { _stop = stop; _status = false; }

protected:
  bool _status = true;
  std::atomic<bool> _stop = false;
};