#include "TrafficLight.h"
#include "TrafficLightBlobDetector.h"
#include "TrafficLightDeepLearning.h"

namespace Vision
{
  namespace TrafficLight
  {
    Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output)
    {
      if (((TrafficLight::Parameters*)params)->GetMode() == Parameters::Mode::BlobDetector)
        return new BlobDetector::BlobDetector(params, input, output);
      else
        return new DeepLearning::DeepLearning(params, input, output);
    }

    Base::Base(IParameters *params, IData *input, IData *output) : IDetect(params, input, output)
    {

    }
  }
}