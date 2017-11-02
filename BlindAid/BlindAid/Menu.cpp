#include "Menu.h"

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

using namespace std;
using namespace cv;

MainMenu::MainMenu() : _core(&_params, NULL, &_results)
{
  // TODO: if(file exists)
  // LoadConfiguration()
  // else
  // SaveConfiguration() ... to save the default configuration specified in each class's Parameters class.

  SaveConfiguration saveConfig(&_params, "BlindAid.cfg");
  saveConfig();

  LoadConfiguration loadConfig(&_params, "BlindAid.cfg");
  loadConfig();
}

void MainMenu::operator()()
{
  char in;
  cout << "Welcome to BlindAid!\n\n";

  do {
    cout << "\
+== Main Menu ==+\n\
| 1: Realtime   |\n\
| 2: Simulate   |\n\
| 3: Settings   |\n\
+===============+\n";

    in = _getch();

    switch (in)
    {
    case '1':
      Realtime();
      break;
    case '2':
      Simulate();
      break;
    case '3':
      Settings();
      break;
    }
    system("cls");
  } while (in != 'q' && in != 'Q');
}

void MainMenu::Realtime()
{
  _params.GetCaptureParams()->SetMode(IParameters::Mode::Realtime);
  _params.GetControlParams()->SetMode(IParameters::Mode::Realtime);

  _core();
}

void MainMenu::Simulate()
{
  char in;
  system("cls");

  do {
    system("cls");
    
    cout << "\
+========= Simulation ========+\n\
| 1: Load Photo               |\n\
| 2: Load Video               |\n\
| d: Depth Obstacle Detector  |\n\
| t: Traffic Light Detector   |\n\
| s: Stop Sign Detector       |\n\
| v: Video Simulation         |\n\
+=============================+\n";

    in = _getch();

    switch (in)
    {
    case '1':
      LoadFile(Capture::Parameters::MediaType::Photo, "depthMap.png");
      break;
    case '2':
      LoadFile(Capture::Parameters::MediaType::Video, "depthMap.png");
      break;
    case 'd':
      TestPhoto("TrafficLight\\tlight", "depthMap.png", 1);
      break;
    case 't':
      TestPhoto("TrafficLight\\tlight", "depthMap.png", 15);
      break;
    case 's':
      TestPhoto("StopSign\\stop", "depthMap.png", 8);
      break;
    case 'v':
      TestVideo("TrafficLight\\tlight", "depthMap.png", 4);
      break;
    }
  } while (in != 'q' && in != 'Q');
}

void MainMenu::Settings()
{

}

void MainMenu::LoadFile(Capture::Parameters::MediaType mode, string depthPath)
{
  string name;
  cout << "Enter file name (default directory): ";
  cin >> name;

  _params.GetCaptureParams()->SetMode(IParameters::Mode::Simulate);
  _params.GetControlParams()->SetMode(IParameters::Mode::Simulate);
  _params.GetDisplayParams()->SetToggle(IParameters::Toggle::Enabled);
  _params.GetCaptureParams()->SetMediaType(mode);
  _params.GetCaptureParams()->SetDepthSimDataPath(PATH + depthPath);
  _params.GetCaptureParams()->SetColorSimDataPath(PATH + name);

  _core();
  waitKey();
}

void MainMenu::TestVideo(string colorVideoPath, string depthPath, int count)
{
  _params.GetCaptureParams()->SetMode(IParameters::Mode::Simulate);
  _params.GetControlParams()->SetMode(IParameters::Mode::Simulate);
  _params.GetDisplayParams()->SetToggle(IParameters::Toggle::Enabled);
  _params.GetCaptureParams()->SetMediaType(Capture::Parameters::MediaType::Video);
  _params.GetCaptureParams()->SetDepthSimDataPath(PATH + depthPath);

  for (int i = 1; i <= count; ++i)
  {
    _params.GetCaptureParams()->SetColorSimDataPath(PATH + colorVideoPath + std::to_string(i) + string(".avi"));
    _core();
    waitKey();
  }
}

void MainMenu::TestPhoto(string colorPath, string depthPath, int count)
{
  _params.GetCaptureParams()->SetMode(IParameters::Mode::Simulate);
  _params.GetControlParams()->SetMode(IParameters::Mode::Simulate);
  _params.GetDisplayParams()->SetToggle(IParameters::Toggle::Enabled);
  _params.GetCaptureParams()->SetMediaType(Capture::Parameters::MediaType::Photo);
  _params.GetCaptureParams()->SetDepthSimDataPath(PATH + depthPath);

  for (int i = 1; i <= count; ++i)
  {
    _params.GetCaptureParams()->SetColorSimDataPath(PATH + colorPath + (count != 0 ? std::to_string(i) : "") + string(".jpg"));
    _core();
    waitKey(0);
  }

  destroyAllWindows();
}