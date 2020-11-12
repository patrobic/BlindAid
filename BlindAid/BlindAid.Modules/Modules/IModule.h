#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <iomanip>

#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

#include "IParameters.h"
#include "GlobalParameters.h"
#include "IData.h"
#include "IResult.h"
#include "Logger.h"

class IIModule
{
public:
  virtual void operator()() = 0;
  virtual void Valid() = 0;
  virtual void Clear() = 0;
  virtual void Process() = 0;
};

template<class Params, class Input, class Output>
class IModule : public IIModule
{
public:
  IModule(IParameters *params, IData *input, IData *output, Tools::Logger *logger)
  {
    _params = static_cast<Params*>(params);
    _input = static_cast<Input*>(input);
    _output = static_cast<Output*>(output);
    _logger = logger;
  }

  void operator()()
  {
    if (!_params->GetToggle())
      return;

    Valid();
    //Clear();
    Process();
  }

protected:
  virtual void Valid()
  {
    if (_params != NULL)
      if(!_params->Valid())
        throw std::exception("Parameters not valid.");

    if(_input != NULL)
      if (!_input->Valid())
        throw std::exception("Input not valid.");
  }

  virtual void Clear()
  {
    if(_output != NULL)
      _output->Clear();
  }

  virtual void Process() = 0;

  Params *_params;
  Input *_input;
  Output *_output;
  Tools::Logger *_logger;

  std::chrono::steady_clock::time_point _start = std::chrono::steady_clock::now();
};