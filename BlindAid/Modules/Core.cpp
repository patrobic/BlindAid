#include "Core.h"

#include <Windows.h>

using namespace std;
using namespace std::chrono;

#define NAME "CORE"

namespace Core
{
  Core::Core(IParameters *params, IData *input, IData *output, Logger *logger) : IModule(params, input, output, logger)
  {
    CreateModules();
  }

  void Core::CreateModules()
  {
    _capture = Capture::Base::MakeCapture(_params->GetCaptureParams(), NULL, _output->GetCaptureResults(), _logger);
    _vision = new Vision::Vision(_params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults(), _logger);
    _control = Control::Base::MakeControl(_params->GetControlParams(), _output->GetVisionResults(), _output->GetCaptureResults(), _logger);
    _display = new Display::Display(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults(), _logger);
    _record = new Record::Record(_params->GetRecordParams(), _output->GetVisionResults(), _output->GetCaptureResults(), _logger);
  }

  void Core::Process()
  {
    _first = steady_clock::now();

    do
    {
      _start = steady_clock::now();

      RunModules();

      if (_output->GetCaptureResults()->GetStop())
        return;
      if (!_output->GetCaptureResults()->GetStatus())
        continue;

      LogStats();

      if (GetAsyncKeyState(VK_ESCAPE))
        break;
    } while (_params->GetCaptureParams()->GetSimulateParams()->GetMediaType() != Capture::Simulate::Parameters::MediaType::Photo || _frame < _params->GetRepeat() || _params->GetRepeat() == 0);
  }

  void Core::RunModules()
  {
    try
    {
      (*_capture)();
      if (!_output->GetCaptureResults()->GetStatus() || _output->GetCaptureResults()->GetStop())
        return;
      
      (*_vision)();
      (*_control)();
      (*_display)();
      (*_record)();
    }
    catch (exception e)
    {
      cout << e.what();
    }
  }

  void Core::LogStats()
  {
    stringstream ss;

    _maxTime = max(_maxTime, (int)(duration_cast<chrono::duration<double>>(steady_clock::now() - _start).count() * 1000));
    _totalTime += duration_cast<chrono::duration<double>>(steady_clock::now() - _start).count();

    ss << "[Frame #" << setw(5) << _frame++ << "] (mean="
      << setw(4) << (int)(_totalTime * 1000 / _frame) << "ms, max="
      << setw(4) << _maxTime << "ms, total="
      << setw(6) << setprecision(1) << fixed << _totalTime << "s, rate="
      << setw(5) << setprecision(2) << fixed << _frame / duration_cast<chrono::duration<double>>(steady_clock::now() - _first).count() << "f/s)";

    LOG(Warning, ss.str(), _start);

    if ((int)*_params->GetGlobalParameters()->GetLogLevel() > (int)LogLevel::Warning)
      cout << endl;
  }
}