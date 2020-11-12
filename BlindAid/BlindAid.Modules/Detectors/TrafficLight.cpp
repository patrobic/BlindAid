#include "TrafficLight.h"
#include "TrafficLightBlobDetector.h"
#include "TrafficLightDeepLearning.h"

namespace Vision
{
  namespace TrafficLight
  {
    Base *Base::MakeTrafficLight(IParameters *params, IData *input, IData *output, Logger *logger)
    {
      if (((TrafficLight::Parameters*)params)->GetVersion() == Parameters::Version::BlobDetector)
        return new BlobDetector::BlobDetector(params, input, output, logger);
      else
        return new DeepLearning::DeepLearning(params, input, output, logger);
    }

    Base::~Base()
    {

    }
    
    Base::Base(IParameters *params, IData *input, IData *output, Logger *logger) : IDetect(params, input, output, logger)
    {

    }
  }
}