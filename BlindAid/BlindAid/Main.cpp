#include "Main.h"
#include <conio.h>

#define PATH "C:\\Projects\\BlindAid\\TestImages\\"
#define DEPTH PATH + string("DepthMap.png")

void main()
{
  Main main;
  main.Init();
  main.Start();
}

void Main::Init()
{
  _dod.Init(&_params, &_image, &_results);
 
  _params.GetTrafficLightParams().SetMode(TrafficLightParams::BlobDetectorMode);
  _tld.Init(&_params, &_image, &_results);

  _ssd.Init(&_params, &_image, &_results);
}

void Main::Start()
{
  cout << "Welcome to BlindAid!\n\n\
+========= Main Menu =========+\n\
| 0: Load File                |\n\
| 1: Settings                 |\n\
| 2: Calibrate                |\n\
| 3: Start Detection          |\n\
| d: Depth Obstacle Detector  |\n\
| t: Traffic Light Detector   |\n\
| s: Stop Sign Detector       |\n\
| v: Video Simulation         |\n\
| p: Photo Simulation         |\n\
+=============================+\n";

  char in;

  do { 
    in = _getch();

    switch (in)
    {
    case '0':
      LoadFile();
    case 'd':
      TestDod();
      break;
    case 't':
      TestTld();
      break;
    case 's':
      TestSsd();
      break;
    case 'v':
      TestVideo();
      break;
    case 'p':
      TestPhoto();
      break;
    }
  } while (in != 'q' || in != 'Q');

  system("pause");
  return;
}

void Main::LoadFile()
{
  string name;
  cout << "Enter file name (default directory): ";
  cin >> name;

  _core.Simulate(false, PATH + name, DEPTH);
  cv::waitKey();
}

void Main::TestDod()
{
  string names[] = { "DepthMap.png" };
 
  for (int i = 0; i < 1; ++i)
  {
    _core.Simulate(false, PATH + names[i], DEPTH);
    cv::waitKey();
  }
}

void Main::TestTld()
{
  for (int i = 2; i <= 5; ++i)
  {
    string name = string("tlight") + std::to_string(i) + string(".jpg");

    _core.Simulate(false, PATH + name, DEPTH);
    waitKey();
  }
}

void Main::TestSsd()
{
  for (int i = 1; i < 8; ++i)
  {
    string name = string("stop") + std::to_string(i) + string(".jpg");

    _core.Simulate(false, PATH + name, DEPTH);
    cv::waitKey();
  }
}

void Main::TestVideo()
{
  string name = "TrafficLight.mp4";

  for (int i = 0; i < 4; ++i)
  {
    _core.Simulate(true, PATH + name, DEPTH);
    //_core.Simulate(PATH + string("tlight") + std::to_string(i) + string(".avi"));
  }
}

void Main::TestPhoto()
{
  string sample = "tlight2.jpg";

  _core.Simulate(false, PATH + sample, DEPTH);
}