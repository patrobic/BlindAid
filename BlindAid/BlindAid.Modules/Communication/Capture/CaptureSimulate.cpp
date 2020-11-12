#include "CaptureSimulate.h"

#include <fstream>
#include <filesystem>

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

    Simulate::~Simulate()
    {

    }

    void Simulate::Process()
    {
      _start = steady_clock::now();

      LoadImageFiles();

      if (!_output->GetStop())
        LOG(Info, "Images acquired from disk (" + _colorName + ", " + _depthName + ")", "SIMULATE", _start);
    }

    void Simulate::LoadImageFiles()
    {
      _output->_colorImageMutex.lock();

      if ((_params->GetGlobalParameters()->GetType() & Color) == Color)
        LoadColorStream();
      if ((_params->GetGlobalParameters()->GetType() & Depth) == Depth)
        LoadDepthStream();

      _index++;
      _output->_colorImageMutex.unlock();
      _output->_newColorFrame = true;
    }

    void Simulate::LoadColorStream()
    {
      if (!std::experimental::filesystem::exists(_params->GetSimulateParams()->GetColorSimDataPath() + "\\" + "color_" + to_string(_index) + ".png"))
        _index = 0;

        _colorName = "color_" + to_string(_index) + ".png";
        *_output->GetColorImage() = imread(_params->GetSimulateParams()->GetColorSimDataPath() + "\\" + _colorName);
        if (_output->GetColorImage()->cols == 0 || _output->GetColorImage()->rows == 0)
          _output->SetStop(true);
    }

    void Simulate::LoadDepthStream()
    {
      if (!std::experimental::filesystem::exists(_params->GetSimulateParams()->GetColorSimDataPath() + "\\" + "depth_" + to_string(_index) + ".tiff"))
        _index = 0;

        _depthName = "depth_" + to_string(_index) + ".tiff";
        *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath() + "\\" + _depthName, IMREAD_UNCHANGED);
        if (_output->GetDepthImage()->cols == 0 || _output->GetDepthImage()->rows == 0)
          _output->SetStop(true);
    }
  }
}