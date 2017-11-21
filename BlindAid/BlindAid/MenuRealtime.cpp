#include <iostream>
#include <conio.h>

#include "MenuRealtime.h"

using namespace std;
using namespace cv;

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

RealtimeMenu::RealtimeMenu(Core::Core *core, Core::Parameters *params, Core::Data *data)
{
  _core = core;
  _params = params;
  _results = data;
}

void RealtimeMenu::operator()()
{
  ShowMenu();
}

void RealtimeMenu::ShowMenu()
{
  char in;
  system("cls");

  do {
    SetParameters();

    system("cls");

    cout << "\
+========== Realtime =========+\n\
| c: Realtime Capture         |\n\
| t: Realtime Control         |\n\
| r: Realtime Capture+Record  |\n\
+=============================+\n";

    in = _getch();

    switch (in)
    {
    case 'c':
      TestRealtimeCapture();
      break;
    case 't':
      TestRealtimeControl("TrafficLight\\tlight1.jpg", "depthMap.png", 1);
      break;
    case 'r':
      TestRecord("Record");
    }
  } while (in != 'q' && in != 'Q');
}

void RealtimeMenu::SetParameters()
{
  _params->Defaults();
  _params->GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Disabled);
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Realtime);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Realtime);
}

void RealtimeMenu::Process()
{
  if (_core == NULL)
    _core = new Core::Core(_params, NULL, _results);

  (*_core)();
}

void RealtimeMenu::TestRealtimeCapture()
{
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Realtime);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetVisionParams()->GetDepthObstacleParams()->SetToggle(SwitchableParameters::Toggle::Disabled);
  _params->GetVisionParams()->GetStopSignParams()->SetToggle(SwitchableParameters::Toggle::Disabled);
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Video);
  _params->GetCaptureParams()->SetType(SwitchableParameters::Type::Color);

  Process();
  destroyAllWindows();
}

void RealtimeMenu::TestRealtimeControl(string colorPath, string depthPath, int count)
{
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Realtime);
  _params->GetVisionParams()->GetDepthObstacleParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
  _params->GetVisionParams()->GetStopSignParams()->SetToggle(SwitchableParameters::Toggle::Disabled);
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Photo);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);
  _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + colorPath);
  _params->SetRepeat(10000);

  Process();
  destroyAllWindows();
}

void RealtimeMenu::TestRecord(string path)
{
  _params->GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
  _params->GetRecordParams()->SetType(SwitchableParameters::Type::Color);
  _params->GetCaptureParams()->SetType(SwitchableParameters::Type::Color);
  _params->GetRecordParams()->SetPath(PATH);

  TestRealtimeCapture();
}