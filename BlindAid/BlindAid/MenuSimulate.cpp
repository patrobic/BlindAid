#include <iostream>
#include <conio.h>

#include "MenuSimulate.h"

using namespace std;
using namespace cv;

#define PATH "C:\\Users\\Salma\\Documents\\CapstoneML\\BlindAid\\BlindAid\\TestData\\"

SimulateMenu::SimulateMenu(Core::Core *core, Core::Parameters *params, Core::Data *data)
{
  _core = core;
  _params = params;
  _results = data;
}

void SimulateMenu::operator()()
{
  ShowMenu();
}

void SimulateMenu::ShowMenu()
{  
  char in;
  system("cls");

  do {
    SetParameters();

    system("cls");

    cout << "\
+========= Simulation ========+\n\
| 1: Load Photo               |\n\
| 2: Load Video               |\n\
| 3: Load Sequence            |\n\
| d: Depth Obstacle Detector  |\n\
| t: Traffic Light Detector   |\n\
| s: Stop Sign Detector       |\n\
| v: Video Simulation         |\n\
+=============================+\n";

    in = _getch();

    switch (in)
    {
    case '1':
      LoadFile(Capture::Simulate::Parameters::MediaType::Photo, "depthMap.png");
      break;
    case '2':
      LoadFile(Capture::Simulate::Parameters::MediaType::Video, "depthMap.png");
      break;
    case '3':
      TestSequence();
      break;
    case 'd':
      TestPhoto("TrafficLight\\tlight", "DepthObstacle\\depth.png", 1);
      break;
    case 't':
      TestPhoto("UniqueIntersections\\tlight", "DepthObstacle\\depth.png",42);
	 //TestPhoto("TrafficLight\\tlight", "DepthObstacle\\depth.png", 21);
      break;
    case 's':
      TestPhoto("StopSign\\stop", "DepthObstacle\\depth.png", 8);
      break;
    case 'v':
      TestVideo("TrafficLight\\tlight", "DepthObstacle\\depth.png", 4);
      break;
    }
  } while (in != 'q' && in != 'Q');
}

void SimulateMenu::SetParameters()
{
  _params->Defaults();
  _params->GetRecordParams()->SetToggle(SwitchableParameters::Toggle::Disabled);
  _params->GetCaptureParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetControlParams()->SetMode(SwitchableParameters::Mode::Simulate);
  _params->GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
}

void SimulateMenu::Process()
{
  if (_core == NULL)
    _core = new Core::Core(_params, NULL, _results);

  (*_core)();
}

void SimulateMenu::LoadFile(Capture::Simulate::Parameters::MediaType mode, string depthPath)
{
  string name;
  cout << "Enter file name (default directory): ";
  cin >> name;

  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(mode);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);
  _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + name);
  _params->GetVisionParams()->GetTrafficLightParams()->SetConsecutiveCount(0);
  _params->GetVisionParams()->GetDepthObstacleParams()->SetConsecutiveCount(1);

  Process();
  waitKey();
}

void SimulateMenu::TestVideo(string colorVideoPath, string depthPath, int count)
{
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Video);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);

  for (int i = 1; i <= count; ++i)
  {
    _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + colorVideoPath + std::to_string(i) + string(".avi"));
    Process();
    waitKey();
  }
}

void SimulateMenu::TestPhoto(string colorPath, string depthPath, int count)
{
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Photo);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + depthPath);
  _params->GetVisionParams()->GetTrafficLightParams()->SetConsecutiveCount(0);
  _params->GetVisionParams()->GetDepthObstacleParams()->SetConsecutiveCount(1);

  for (int i = 1; i <= count; ++i)
  {
    _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + colorPath + (count != 0 ? std::to_string(i) : "") + string(".jpg"));
    Process();
    waitKey();
  }

  destroyAllWindows();
}

void SimulateMenu::TestSequence()
{
  _params->GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Sequence);
  _params->GetVisionParams()->GetTrafficLightParams()->SetConsecutiveCount(0);
  _params->GetVisionParams()->GetDepthObstacleParams()->SetConsecutiveCount(1);

  string path;
  cout << "Enter folder name (date): ";
  cin >> path;

  _params->GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + path);
  _params->GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + path);
  _results->GetCaptureResults()->SetStatus(true);

  while(_results->GetCaptureResults()->GetStatus())
    Process();

  destroyAllWindows();
}