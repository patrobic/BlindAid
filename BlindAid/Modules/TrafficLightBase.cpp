#include "TrafficLightBase.h"
#include "TrafficLightBlobDetector.h"
#include "TrafficLightDeepLearning.h"

namespace Vision
{
  namespace TrafficLight
  {
    Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output)
    {
      if (params->GetMode() == Parameters::Mode::BlobDetector)
        return new BlobDetector(params, input, output);
      else
        return new DeepLearning(params, input, output);
    }

    Base::Base(IParameters *params, IData *input, IData *output) : DetectBase(params, input, output)
    {

    }

  }
}