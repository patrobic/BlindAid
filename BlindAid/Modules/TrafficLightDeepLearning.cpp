#include "TrafficLightDeepLearning.h"

using namespace std;
using namespace cv;

namespace Vision {
  namespace TrafficLight {
    namespace DeepLearning {
      DeepLearning::DeepLearning(IParameters *params, IData *input, IData *output) : Base(params, input, output)
      {
        _output->SetParams(_params->GetConsecutiveCount(), _params->GetMaximumDistance(), _params->GetMaximumRadiusDiff());

        // Initialize python environment.
        Py_Initialize();
      }

      void DeepLearning::Process()
      {
        PreprocessImage();
        RunDeepLearning();
        UpdateResults();
      }

      void DeepLearning::PreprocessImage()
      {
        // Get the color image, crop to only the top half (since traffic lights are only expected in upper fraction of frame), and resize to size required by deep learning.
        resize((*_input->GetRgbImage())(Rect((int)(_input->GetRgbImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2), 0, (int)(_input->GetRgbImage()->cols *  _params->GetCenterRegionRatio()), (int)(_input->GetRgbImage()->rows*_params->GetUpperRegionRatio()))), _preprocessedImage, _params->GetDeepLearningParams()->GetColorImageSize());

        // convert/assign opencv mat to python pyobject (numpy arrray).
        // TODO: _pyColorImage = _prprocessedImage.ptr(0);
      }

      void DeepLearning::RunDeepLearning()
      {
        // TODO: integrate with deep learning API of choice.
        // 1. Call deep learning traffic light detection [python] function.
        // 2. Retrieve results (if necessary) in _pyCOLORConfidence variable.

        // TEMP: store dummy values for testing.
        _pyRedConfidence = PyFloat_FromDouble(0.05);
        _pyGreenConfidence = PyFloat_FromDouble(0.15);
        _pyNoneConfidence = PyFloat_FromDouble(0.8);
      }

      void DeepLearning::UpdateResults()
      {
        float red = (float)PyFloat_AsDouble(_pyRedConfidence);
        float green = (float)PyFloat_AsDouble(_pyGreenConfidence);
        float none = (float)PyFloat_AsDouble(_pyNoneConfidence);

        float confidence[3] = { red, green, none };

        if (red > green && red > none && red > _params->GetDeepLearningParams()->GetConfidenceThreshold())
          _output->Set(Result::Red, confidence);
        else if (green > red && green > none && green > _params->GetDeepLearningParams()->GetConfidenceThreshold())
          _output->Set(Result::Green, confidence);
        else
          _output->Set(Result::None, confidence);
      }
    }
  }
}