#include "CaptureSimulate.h"

#include <fstream>
#include <filesystem>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::filesystem;
using namespace cv;

#define NAME "CAPTURE"

namespace Capture
{
  namespace Simulate
  {
    CaptureSimulate::CaptureSimulate(IParameters* params, IData* input, IData* output, Tools::Logger* logger) : Capture(params, input, output, logger)
    {
      _index = _params->GetSimulateParams()->GetStartIndex();
    }

    CaptureSimulate::~CaptureSimulate()
    {

    }

    void CaptureSimulate::Process()
    {
      _start = steady_clock::now();

      LoadImageFiles();

      if (!_output->GetStop())
        LOG(Tools::Info, "Images acquired from disk (" + _colorName + ", " + _depthName + ")", "SIMULATE", _start);
    }

    void CaptureSimulate::LoadImageFiles()
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

    void CaptureSimulate::LoadColorStream()
    {
      if (!exists(_params->GetSimulateParams()->GetColorSimDataPath() + "\\" + "color_" + to_string(_index) + ".png"))
        _index = _params->GetSimulateParams()->GetStartIndex();

      _colorName = "color_" + to_string(_index) + ".png";
      *_output->GetColorImage() = imread(_params->GetSimulateParams()->GetColorSimDataPath() + "\\" + _colorName);
      if (_output->GetColorImage()->cols == 0 || _output->GetColorImage()->rows == 0 || _index >= _params->GetSimulateParams()->GetEndIndex())
        _output->SetStop(true);
    }

    void CaptureSimulate::LoadDepthStream()
    {
      if (!exists(_params->GetSimulateParams()->GetColorSimDataPath() + "\\" + "depth_" + to_string(_index) + ".tiff"))
        _index = _params->GetSimulateParams()->GetStartIndex();

      _depthName = "depth_" + to_string(_index) + ".tiff";
      *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath() + "\\" + _depthName, IMREAD_UNCHANGED);
      if (_output->GetDepthImage()->cols == 0 || _output->GetDepthImage()->rows == 0 || _index >= _params->GetSimulateParams()->GetEndIndex())
        _output->SetStop(true);
    }
  }
}