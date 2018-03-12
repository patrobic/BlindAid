#include "CaptureSimulate.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

#define NAME "CAPTURE"

namespace Capture
{
  namespace Simulate
  {
    Simulate::Simulate(IParameters *params, IData *input, IData *output, Logger *logger) : Base(params, input, output, logger)
    {

    }

    void Simulate::Process()
    {
      _start = steady_clock::now();

      LoadFile();
      CreateHsvImage();

      LOG(Info, "Images acquired from disk", "SIMULATE", _start);
    }

    void Simulate::LoadFile()
    {
      _output->_colorImageMutex.lock();

      if (_params->GetSimulateParams()->GetMediaType() == Parameters::MediaType::Video)
        LoadVideo();
      else if (_params->GetSimulateParams()->GetMediaType() == Parameters::MediaType::Photo)
        LoadPhoto();
      else
        LoadSequence();

      _output->_colorImageMutex.unlock();
      _output->_newColorFrame = true;
    }

    void Simulate::LoadVideo()
    {
      if (!_cap.isOpened())
        _cap.open(_params->GetSimulateParams()->GetColorSimDataPath());

      _cap.read(*_output->GetColorImage());
      *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath());
    }

    void Simulate::LoadPhoto()
    {
      *_output->GetColorImage() = imread(_params->GetSimulateParams()->GetColorSimDataPath());
      *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath(), CV_16UC1);

      if (_output->GetColorImage()->cols == 0 || _output->GetColorImage()->rows == 0) throw("could not open image.");
    }

    void Simulate::LoadSequence()
    {
      string path = _params->GetSimulateParams()->GetColorSimDataPath() + "\\color_" + to_string(_index) + ".jpg";
      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
      {
        *_output->GetColorImage() = imread(_params->GetSimulateParams()->GetColorSimDataPath() + "\\color_" + to_string(_index) + ".jpg");
        if (_output->GetColorImage()->cols == 0 || _output->GetColorImage()->rows == 0)
          _output->SetStatus(false);
      }

      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
      {
        *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath() + "\\depth_" + to_string(_index) + ".jpg");
        if (_output->GetDepthImage()->cols == 0 || _output->GetDepthImage()->rows == 0)
          _output->SetStatus(false);
      }

      ++_index;
    }
  }
}