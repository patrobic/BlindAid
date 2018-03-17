#pragma once

#include "IDetect.h"
#include "Capture.h"
#include "TrafficLightData.h"

namespace Vision
{
  namespace TrafficLight
  {
    class Base : public IDetect<Parameters, Capture::Data, Data>
    {
    public:
      Base(IParameters *params, IData *input, IData *output, Logger *logger);
      virtual ~Base();
      static Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output, Logger *logger);

    protected:
    };
  }
}