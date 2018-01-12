#include "TrafficLightDeepLearning.h"

using namespace std;
using namespace cv;

namespace Vision {
  namespace TrafficLight {
    namespace DeepLearning {
      DeepLearning::DeepLearning(IParameters *params, IData *input, IData *output) : Base(params, input, output)
      {
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
        resize((*_input->GetColorImage())(Rect((int)(_input->GetColorImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2), 0, (int)(_input->GetColorImage()->cols *  _params->GetCenterRegionRatio()), (int)(_input->GetColorImage()->rows*_params->GetUpperRegionRatio()))), _preprocessedImage, _params->GetDeepLearningParams()->GetColorImageSize());

        // convert/assign opencv mat to python pyobject (numpy arrray).
        // TODO: _pyColorImage = _prprocessedImage.ptr(0);
      }

      void DeepLearning::RunDeepLearning()
      {
        // TODO: integrate with deep learning API of choice.
        // 1. Call deep learning traffic light detection [python] function.
        // 2. Retrieve results (if necessary) in _pyCOLORConfidence variable.

        // TEMP: store dummy values for testing.
        float confidence[4] = { 0.6f, 0.15f, 0.05f, 0.2f };
        for (int i = 0; i < 4; ++i)
          _pyConfidence[i] = PyFloat_FromDouble(confidence[i]);
      }

      void DeepLearning::UpdateResults()
      {
        for (int i = 0; i < 4; ++i)
          _confidence[i] = (float)PyFloat_AsDouble(_pyConfidence[i]);

        for (int i = 0; i < 4; ++i)
        {
          bool success = true;
          for (int j = 0; j < 4; ++j)
          {
            if (_confidence[i] < _confidence[j])
              success = false;
          }
          if (success)
            _output->Set(Result(_confidence));
        }
      }
    }
  }
}