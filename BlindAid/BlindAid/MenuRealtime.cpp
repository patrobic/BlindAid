#include "MenuRealtime.h"

using namespace std;
using namespace cv;

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

RealtimeMenu::RealtimeMenu(Core::Core *core, Core::Parameters *params, Core::Data *data, Logger *logger, Configuration *config) : Menu(core, params, data, logger, config)
{

}

void RealtimeMenu::ShowMenu()
{
  char in;
  system("cls");

  do {
    system("cls");

    cout << "\
+========== Realtime =========+\n\
| a: Realtime Production      |\n\
| c: Realtime Capture         |\n\
| t: Realtime Control         |\n\
| r: Realtime Capture+Record  |\n\
+=============================+\n";

    in = _getch();

    switch (in)
    {
    case 'a':
      TestRealtimeComplete();
      break;
    case 'c':
      TestRealtimeCapture();
      break;
    case 't':
      TestRealtimeControl("TrafficLight\\tlight1.jpg", "DepthObstacle\\depth.png", 1);
      break;
    case 'r':
      TestRecord("Record");
    }
  } while (in != 'q' && in != 'Q');
}

void RealtimeMenu::TestRealtimeComplete()
{
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Realtime);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Realtime);

  Process();
}

void RealtimeMenu::TestRealtimeCapture()
{
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Realtime);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);

  Process();
}

void RealtimeMenu::TestRealtimeControl(string colorPath, string depthPath, int count)
{
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Realtime);
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Photo);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);
  _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + colorPath);

  Process();
}

void RealtimeMenu::TestRecord(string path)
{
  _params->GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
  _params->GetRecordParams()->SetPath(PATH + path);

  TestRealtimeCapture();
}