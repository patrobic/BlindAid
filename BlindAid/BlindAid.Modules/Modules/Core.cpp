#include "Core.h"

#include <Windows.h>

using namespace std;
using namespace std::chrono;

#define NAME "CORE"

namespace Core
{
  Core::Core(IParameters *params, IData *input, IData *output, Logger *logger) : IModule(params, input, output, logger)
  {
    _capture = Capture::Capture::MakeCapture(_params->GetCaptureParams(), NULL, _output->GetCaptureResults(), _logger);
    _vision = new Vision::Vision(_params->GetVisionParams(), _output->GetCaptureResults(), _output->GetVisionResults(), _logger);
    _control = Control::Control::MakeControl(_params->GetControlParams(), _output->GetVisionResults(), _output->GetCaptureResults(), _logger);
    _display = new Display::Display(_params->GetDisplayParams(), _output->GetVisionResults(), _output->GetCaptureResults(), _logger);
    _record = new Record::Record(_params->GetRecordParams(), _output->GetVisionResults(), _output->GetCaptureResults(), _logger);
  }

  Core::~Core()
  {
    delete _record;
    delete _display;
    delete _control;
    delete _vision;
    delete _capture;
  }

  void Core::Process()
  {
    _first = steady_clock::now();

    while (true)
    {
      _start = steady_clock::now();

      RunModules();

      if (_output->GetCaptureResults()->GetStatus())
        LogStats();

      if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        _output->GetCaptureResults()->SetStop(true);

      if (_output->GetCaptureResults()->GetStop())
      {
        if (_params->GetGlobalParameters()->GetMenuEnabled() && _params->GetMode() == Simulate)
           system("pause");

        system("cls");
        cv::destroyAllWindows();

        if (_params->GetGlobalParameters()->GetMenuEnabled())
          return;
        else
          exit(0);
      }
    }
  }

  void Core::RunModules()
  {
    (*_capture)();
    if (!_output->GetCaptureResults()->GetStatus())
      return;

    (*_vision)();
    (*_control)();
    (*_display)();
    (*_record)();
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