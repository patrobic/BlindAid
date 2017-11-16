#include "CaptureSimulate.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Capture
{
  namespace Simulate
  {
    Simulate::Simulate(IParameters *params, IData *input, IData *output) : Base<Parameters>(params, input, output)
    {

    }

    void Simulate::Process()
    {
      if (_params->GetMediaType())
      {
        if (!_cap.isOpened())
          _cap.open(_params->GetColorSimDataPath());

        LoadVideo();
      }
      else
        LoadPhoto();

      CreateHsvImage();
    }

    void Simulate::LoadVideo()
    {
      steady_clock::time_point start = steady_clock::now();

      _cap.read(*_output->GetRgbImage());
      *_output->GetDepthImage() = imread(_params->GetDepthSimDataPath());

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);

      cout << "[CAPTURESIM] Video frame #" << to_string(_frame) << " loaded (" << time_span.count() * 1000 << "ms).\n";

      _frame++;
    }

    void Simulate::LoadPhoto()
    {
      steady_clock::time_point start = steady_clock::now();

      *_output->GetRgbImage() = imread(_params->GetColorSimDataPath());
      *_output->GetDepthImage() = imread(_params->GetDepthSimDataPath());
      if (_output->GetRgbImage()->cols == 0 || _output->GetRgbImage()->rows == 0) throw("could not open image.");

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);

      cout << "[CAPTURESIM] Photo frame loaded (" << time_span.count() * 1000 << "ms).\n";
    }
  }
}