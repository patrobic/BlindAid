#include "CaptureSimulate.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Capture
{
  namespace Simulate
  {
    Simulate::Simulate(IParameters *params, IData *input, IData *output) : Base(params, input, output)
    {

    }

    void Simulate::Process()
    {
      steady_clock::time_point start = steady_clock::now();

      if (_params->GetSimulateParams()->GetMediaType())
        LoadVideo();
      else
        LoadPhoto();

      CreateHsvImage();

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);

      cout << "[CAPTURE] Frame loaded (" << time_span.count() * 1000 << "ms).\n";
    }

    void Simulate::LoadVideo()
    {
      if (!_cap.isOpened())
        _cap.open(_params->GetSimulateParams()->GetColorSimDataPath());

      _cap.read(*_output->GetRgbImage());
      *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath());
    }

    void Simulate::LoadPhoto()
    {
      *_output->GetRgbImage() = imread(_params->GetSimulateParams()->GetColorSimDataPath());
      *_output->GetDepthImage() = imread(_params->GetSimulateParams()->GetDepthSimDataPath());

      if (_output->GetRgbImage()->cols == 0 || _output->GetRgbImage()->rows == 0) throw("could not open image.");
    }
  }
}