#include "TrafficLightDeepLearning.h"

using namespace std;
using namespace std::chrono;
using namespace cv;
using namespace cv::dnn;

namespace Vision 
{
  namespace TrafficLight 
  {
    namespace DeepLearning 
    {
      DeepLearning::DeepLearning(IParameters *params, IData *input, IData *output) : Base(params, input, output)
      {
        LoadNetwork();
      }

      void DeepLearning::LoadNetwork()
      {
        _net = readNetFromTensorflow(_path + "model.pb", _path + "modeln.pbtxt");
        if (_net.empty())
          throw("Can't load network by using the model file.");
      }

      void DeepLearning::Process()
      {
        steady_clock::time_point start = steady_clock::now();

        PreprocessImage();
        MachineLearning();
        UpdateResults();

        steady_clock::time_point end = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(end - start);
        cout << "[TRAF-DL] Traffic lights detected.\t(" << setw(5) << (int)(time_span.count() * 1000) << " ms)\n";
        cout << "  [COLOR] " << _output->_names[_map[_classId]] << " (" << setprecision(3) << _classProb * 100 << "%).\n";
      }

      void DeepLearning::PreprocessImage()
      {
        resize((*_input->GetColorImage())(Rect((int)(_input->GetColorImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2), 0,
          (int)(_input->GetColorImage()->cols *  _params->GetCenterRegionRatio()),
          (int)(_input->GetColorImage()->rows*_params->GetUpperRegionRatio()))),
          _preprocessedImage, _params->GetDeepLearningParams()->GetColorImageSize());
      }

      void DeepLearning::MachineLearning()
      {
        _inputBlob = blobFromImage(_preprocessedImage, 1.0 / 255.0f, Size(224, 224), Scalar(0, 0, 0), true, true);

        _net.setInput(_inputBlob);
        _result = _net.forward();
      }

      void DeepLearning::UpdateResults()
      {
        minMaxLoc(_result.reshape(1, 1), NULL, &_classProb, NULL, &_classNumber);
        _classId = _classNumber.x;

        for (int i = 0; i < 3; ++i)
          _confidence[_map[i]] = max(0.f, _result.at<float>(i));

        _output->Set(Result(_confidence));
      }
    }
  }
}