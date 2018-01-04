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
      }

      void DeepLearning::PreprocessImage()
      {
        // Get the color image, crop to only the top half (since traffic lights are only expected in upper fraction of frame), and resize to size required by deep learning.
        resize((*_input->GetRgbImage())(Rect(0, 0, _input->GetRgbImage()->cols, (int)(_input->GetRgbImage()->rows*_params->GetUpperRegionToAnalyze()))), _preprocessedImage, _params->GetDeepLearningParams()->GetColorImageSize());

        // Assign python image object to opencv mat.
        // TODO: _pyColorImage = _prprocessedImage.ptr(0);
        
      }
        
      void DeepLearning::RunDeepLearning()
      {
        // TODO
        // integrate with deep learning API of choice.
   


        // TEMP: store dummy values.
        _pyRedConfidence = PyFloat_FromDouble(0.8);
        _pyGreenConfidence = PyFloat_FromDouble(0.15);
        _pyNoneConfidence = PyFloat_FromDouble(0.05);
      }

      void DeepLearning::StoreResults()
      {
        float red = (float)PyFloat_AsDouble(_pyRedConfidence);
        float green = (float)PyFloat_AsDouble(_pyGreenConfidence);
        float none = (float)PyFloat_AsDouble(_pyNoneConfidence);

        if (red > green && red > none && red > _params->GetDeepLearningParams()->GetConfidenceThreshold())
          _output->SetSingle(Result::Red);
        else if (green > red && green > none && green > _params->GetDeepLearningParams()->GetConfidenceThreshold())
          _output->SetSingle(Result::Green);
        else
          _output->SetSingle(Result::None);
      }
    }
  }
}