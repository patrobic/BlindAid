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
        // GetFiltered the color image, crop to only the top half (since traffic lights are only expected in upper fraction of frame), and resize to size required by deep learning.
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
        _pyRedConfidence = PyFloat_FromDouble(0.6);
        _pyGreenConfidence = PyFloat_FromDouble(0.15);
        _pyYellowConfidence = PyFloat_FromDouble(0.05);
        _pyNoneConfidence = PyFloat_FromDouble(0.2);
      }

      void DeepLearning::UpdateResults()
      {
        float confidence[4] = { (float)PyFloat_AsDouble(_pyRedConfidence), (float)PyFloat_AsDouble(_pyGreenConfidence), (float)PyFloat_AsDouble(_pyYellowConfidence), (float)PyFloat_AsDouble(_pyNoneConfidence) };

        for (int i = 0; i < 4; ++i)
        {
          bool success = true;
          for (int j = 0; j < 4; ++j)
          {
            if (confidence[i] < confidence[j])
              success = false;
          }
          if (success)
            _output->Set(Result(confidence));
        }
      }
    }
  }
}