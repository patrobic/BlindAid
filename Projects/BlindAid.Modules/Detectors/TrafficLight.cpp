#include "TrafficLight.h"
#include "TrafficLightBlobDetector.h"
#include "TrafficLightDeepLearning.h"

namespace Vision
{
  namespace TrafficLight
  {
    TrafficLight *TrafficLight::MakeTrafficLight(IParameters *params, IData *input, IData *output, Tools::Logger *logger)
    {
      if (((TrafficLightParameters*)params)->GetVersion() == TrafficLightParameters::Version::BlobDetector)
        return new BlobDetector::BlobDetector(params, input, output, logger);
      else
        return new DeepLearning::DeepLearning(params, input, output, logger);
    }

    TrafficLight::~TrafficLight()
    {

    }
    
    TrafficLight::TrafficLight(IParameters *params, IData *input, IData *output, Tools::Logger *logger) : IDetect(params, input, output, logger)
    {

    }
  }
}