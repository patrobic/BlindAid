#include "Core.h"

using namespace std;
using namespace std::chrono;

namespace Core
{
  Core::Core(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {
  }

  void Core::Process()
  {
    static int frame = 0;

    _capture = Capture::Base::MakeCapture(_params->GetCaptureParams(), NULL, _output->GetCaptureResults());
    _record = new Record::Record(_params->GetRecordParams(), _output->GetCaptureResults(), NULL);
    _vision = new Vision::Vision(_params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults());
    _control = Control::Base::MakeControl(_params->GetControlParams(), _output->GetVisionResults(), _output->GetCaptureResults());
    _display = new Display::Display(_params->GetDisplayParams(), _output->GetVisionResults(), NULL);

    do
    {
      steady_clock::time_point start = steady_clock::now();

      try
      {
        (*_capture)();
        (*_record)();
        (*_vision)();
        (*_control)();
        (*_display)();
      }
      catch (exception e)
      {
        cout << e.what();
      }

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);

      cout << "[CORE] Frame #" << to_string(frame++) << " processed (" << time_span.count() * 1000 << "ms).\n";
    } while (_params->GetCaptureParams()->GetMediaType() == Capture::Parameters::MediaType::Video || frame < _params->GetRepeat());

    delete _capture;
    delete _vision;
    delete _control;
    delete _display;
  }
}