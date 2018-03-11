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
        _net = readNetFromTensorflow(_params->_path + "\\model.pb", _params->_path + "\\modeln.pbtxt");
        if (_net.empty())
          throw("Can't load network by using the model file.");
      }

      void DeepLearning::Process()
      {
        static bool firstRun = true;
        if(firstRun)
          _processThread = new std::thread(&DeepLearning::TProcess, this);

        firstRun = false;
      }

      void DeepLearning::PreprocessImage()
      {
        _input->_colorImageMutex.lock();

        _output->SetRegion(Rect((int)(_input->GetColorImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2), 0,
          (int)(_input->GetColorImage()->cols *  _params->GetCenterRegionRatio()),
          (int)(_input->GetColorImage()->rows*_params->GetUpperRegionRatio())));

        resize((*_input->GetColorImage())(_output->GetRegion()), _preprocessedImage, _params->GetDeepLearningParams()->GetColorImageSize());

        _input->_colorImageMutex.unlock();
        _input->_newColorFrame = false;
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

        _output->_trafficLightMutex.lock();
        _output->Set(Result(_confidence));
        _output->_trafficLightMutex.unlock();
      }

      void DeepLearning::TProcess()
      {
        while (true)
        {
          if (_input->_newColorFrame)
          {
            steady_clock::time_point start = steady_clock::now();

            PreprocessImage();
            MachineLearning();
            UpdateResults();

            steady_clock::time_point end = steady_clock::now();
            duration<double> time_span = duration_cast<duration<double>>(end - start);
            cout << "[TRAF-DL] Traffic lights detected.\t(" << setw(5) << (int)(time_span.count() * 1000) << " ms)\n";

          }
        }
      }
    }
  }
}