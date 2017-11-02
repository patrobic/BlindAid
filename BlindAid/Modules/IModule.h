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
#include "IData.h"

class IModule
{
public:
  class Parameters : public IParameters
  {
  public:

  private:

  };

  class Data: public IData
  {
  public:

  private:

  };

  virtual void operator()() = 0;

protected:
};

class DetectBase : public IModule
{
public:

protected:
};