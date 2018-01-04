#include "TrafficLightDeepLearning.h"

using namespace std;

namespace Vision {
  namespace TrafficLight {
    namespace DeepLearning {
      DeepLearning::DeepLearning(IParameters *params, IData *input, IData *output) : Base(params, input, output)
      {

      }

      void DeepLearning::Process()
      {
        RunDeepLearning();
      }

      void DeepLearning::RunDeepLearning()
      {
        // TODO
        // integrate with deep learning API of choice.

        // Acquire Mat color image.
        _input->GetRgbImage();

        // Write detection results.
        //_output->Set();

      }
    }
  }
}