#pragma once

#include "IDetect.h"
#include "Capture.h"
#include "TrafficLightData.h"

namespace Vision
{
  namespace TrafficLight
  {
    class Base : public IDetect<TrafficLightParameters, Capture::CaptureData, TrafficLightData>
    {
    public:
      Base(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
      virtual ~Base();
      static Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output, Tools::Logger *logger);

    protected:
    };
  }
}