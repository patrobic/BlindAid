#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

#include "IParameters.h"
#include "IResults.h"


struct Data // DEPRECATED! will be removed in the near future!
{
  bool _run;

  std::thread _captureThread;
  std::thread _visionThread;
  std::thread _controlThread;
  std::thread _displayThread;

  std::mutex _bufferMutex;
  std::mutex _currentBufferMutex;
  std::mutex _resultMutex;

  std::atomic_bool _captureDone;
  std::atomic_bool _visionDone;
  std::atomic_bool _newFrameForVision;
  std::atomic_bool _newFrameForControl;
  std::atomic_bool _newFrameForDisplay;

  // DO NOT add anything new to this class. a global Data class is bad practice and breaks many programming rules/conventions.
  // If you need to add new data, it will be in either PARAMETERS or RESULTS (input is included in results).
};

class IModule
{
public:
  class Parameters : public IParameters
  {
  public:

  private:

  };

  class Results: public IResults
  {
  public:

  private:

  };

  //IModule(Data *data, IParameters *params, IResults *input, IResults *output) {};
  virtual void operator()() = 0;

protected:
  Data *_data;
};

class DetectBase : public IModule
{
public:

protected:
};