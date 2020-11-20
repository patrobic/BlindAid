#pragma once

#include "IDetect.h"
#include "Capture.h"
#include "TrafficLightData.h"

namespace Vision
{
  namespace TrafficLight
  {
    class TrafficLight : public IDetect<TrafficLightParameters, Capture::CaptureData, TrafficLightData>
    {
    public:
      TrafficLight(IParameters *params, IData *input, IData *output, Tools::Logger *logger);
      virtual ~TrafficLight();
      static TrafficLight *TrafficLight::MakeTrafficLight(IParameters *params, IData *input, IData *output, Tools::Logger *logger);

    protected:
    };
  }
}