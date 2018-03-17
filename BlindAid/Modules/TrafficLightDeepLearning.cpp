#include "TrafficLightDeepLearning.h"

using namespace std;
using namespace std::chrono;
using namespace cv;
using namespace cv::dnn;

#define NAME "TLIGHT"

namespace Vision
{
  namespace TrafficLight
  {
    namespace DeepLearning
    {
      DeepLearning::DeepLearning(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger)
      {
        LoadNetwork();
      }

      DeepLearning::~DeepLearning()
      {
        _input->SetStop(true);
        delete _processThread;
      }

      void DeepLearning::LoadNetwork()
      {
        _net = readNetFromTensorflow(_params->GetGlobalParameters()->GetExePath() + "\\model.pb", _params->GetGlobalParameters()->GetExePath() + "\\modeln.pbtxt");
        if (_net.empty())
          throw("Can't load network by using the model file.");
      }

      void DeepLearning::Process()
      {
        if (_params->GetMode() == Realtime)
          CreateThread();
        else
          ProcessFunc();
      }

      void DeepLearning::CreateThread()
      {
        if (_firstRun)
          _processThread = new std::thread(&DeepLearning::TProcess, this);

        _firstRun = false;
      }

      void DeepLearning::ProcessFunc()
      {
        _start = steady_clock::now();

        PreprocessImage();
        MachineLearning();
        UpdateResults();

        if (_input->GetStop())
          return;

        LOG(Warning, "Traffic lights detected", "DEEPLEAR", _start);
      }

      void DeepLearning::TProcess()
      {
        while (true)
        {
          if (_input->GetStop())
            return;

          if (_input->_newColorFrame)
            ProcessFunc();
        }
      }

      void DeepLearning::PreprocessImage()
      {
        _input->_colorImageMutex.lock();

        _output->SetRegion(Rect((int)(_input->GetColorImage()->cols * (1 - _params->GetCenterRegionRatio()) / 2), 0,
          (int)(_input->GetColorImage()->cols * _params->GetCenterRegionRatio()),
          (int)(_input->GetColorImage()->rows * _params->GetUpperRegionRatio())));

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
    }
  }
}