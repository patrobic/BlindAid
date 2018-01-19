#include "Core.h"

#include <Windows.h>

using namespace std;
using namespace std::chrono;

namespace Core
{
  Core::Core(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {
    CreateModules();
  }

  void Core::CreateModules()
  {
    _capture = Capture::Base::MakeCapture(_params->GetCaptureParams(), NULL, _output->GetCaptureResults());
    _vision = new Vision::Vision(_params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults());
    _control = Control::Base::MakeControl(_params->GetControlParams(), _output->GetVisionResults(), _output->GetCaptureResults());
    _display = new Display::Display(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults());
    _record = new Record::Record(_params->GetRecordParams(), _output->GetVisionResults(), _output->GetCaptureResults());
  }

  void Core::Process()
  {
    do
    {
      steady_clock::time_point start = steady_clock::now();

      try
      {
        (*_capture)();
        if (!_output->GetCaptureResults()->GetStatus())
          break;

        (*_vision)();
        (*_control)();
        (*_display)();
        (*_record)();
      }
      catch (exception e)
      {
        cout << e.what();
      }

      steady_clock::time_point end = steady_clock::now();
      duration<double> time_span = duration_cast<duration<double>>(end - start);

      cout << "[   CORE] Frame #" << to_string(_frame++) << " processed (" << time_span.count() * 1000 << "ms).\n";

      if (GetAsyncKeyState(VK_ESCAPE))
        break;
    } while (_params->GetCaptureParams()->GetSimulateParams()->GetMediaType() == Capture::Simulate::Parameters::MediaType::Video || _frame < _params->GetRepeat() || _params->GetRepeat() == 0);
  }
}