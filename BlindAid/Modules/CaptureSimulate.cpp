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
      
      if (!_output->GetStop())
        return;

      CreateHsvImage();

      LOG(Info, "Images acquired from disk (" + _colorName + ", " + _depthName + ")", "SIMULATE", _start);
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
      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
      {
        _colorName = "color_" + to_string(_index) + ".png";
        *_output->GetColorImage() = imread(_params->GetSimulateParams()->GetColorSimDataPath() + "\\" + _colorName);
        if (_output->GetColorImage()->cols == 0 || _output->GetColorImage()->rows == 0)
          _output->SetStop(true);
      }

      if (_params->GetType() == SwitchableParameters::Type::Color || _params->GetType() == SwitchableParameters::Type::Both)
      {
        _depthName = "depth_" + to_string(_index) + ".tiff";
        *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath() + "\\" + _depthName, IMREAD_UNCHANGED);
        if (_output->GetDepthImage()->cols == 0 || _output->GetDepthImage()->rows == 0)
          _output->SetStop(true);
      }

      ++_index;
    }
  }
}