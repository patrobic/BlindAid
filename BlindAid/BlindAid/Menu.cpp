#include "Menu.h"

#define PATH "C:\\Projects\\BlindAid\\TestImages\\"

using namespace std;
using namespace cv;

void MainMenu::Init()
{
  _core.Init(&_data);
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
  _data._params.SetCaptureMode(Parameters::Mode::Realtime);
  _data._params.SetControlMode(Parameters::Mode::Realtime);

  _core();
}

void MainMenu::Simulate()
{
  char in;
  system("cls");

  do {
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
      LoadFile(Parameters::MediaType::Photo, "depthMap.png");
      break;
    case '2':
      LoadFile(Parameters::MediaType::Video, "depthMap.png");
      break;
    case 'd':
      TestPhoto("tlight", "depthMap.png", 1);
      break;
    case 't':
      TestPhoto("tlight", "depthMap.png", 4);
      break;
    case 's':
      TestPhoto("stop", "depthMap.png", 8);
      break;
    case 'v':
      TestVideo("tlight", "depthMap.png", 4);
      break;
      system("cls");
    }
  } while (in != 'q' && in != 'Q');
}

void MainMenu::Settings()
{

}

void MainMenu::LoadFile(Parameters::MediaType mode, string depthPath)
{
  string name;
  cout << "Enter file name (default directory): ";
  cin >> name;

  _data._params.SetCaptureMode(Parameters::Mode::Simulate);
  _data._params.SetControlMode(Parameters::Mode::Simulate);
  _data._params.SetMediaType(mode);
  _data._params.SetEnableDisplay(true);
  _data._params.SetDepthSimDataPath(PATH + depthPath);
  _data._params.SetColorSimDataPath(PATH + name);

  _core();
  waitKey();
}

void MainMenu::TestVideo(string colorVideoPath, string depthPath, int count)
{
  _data._params.SetCaptureMode(Parameters::Mode::Simulate);
  _data._params.SetControlMode(Parameters::Mode::Simulate);
  _data._params.SetMediaType(Parameters::MediaType::Video);
  _data._params.SetEnableDisplay(true);
  _data._params.SetDepthSimDataPath(PATH + depthPath);

  for (int i = 1; i <= count; ++i)
  {
    _data._params.SetColorSimDataPath(PATH + colorVideoPath + std::to_string(i) + string(".avi"));
    _core();
    waitKey();
  }
}

void MainMenu::TestPhoto(string colorPath, string depthPath, int count)
{
  _data._params.SetCaptureMode(Parameters::Mode::Simulate);
  _data._params.SetControlMode(Parameters::Mode::Simulate);
  _data._params.SetMediaType(Parameters::MediaType::Photo);
  _data._params.SetEnableDisplay(true);
  _data._params.SetDepthSimDataPath(PATH + depthPath);

  for (int i = 1; i <= count; ++i)
  {
    _data._params.SetColorSimDataPath(PATH + colorPath + (count != 0 ? std::to_string(i) : "") + string(".jpg"));
    _core();
    waitKey();
  }
}