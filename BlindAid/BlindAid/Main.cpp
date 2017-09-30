#include "Main.h"
#include <iostream>
#include <conio.h>

using namespace std;

#define PATH "C:\\Projects\\BlindAid\\TestImages\\"

void main()
{
  Main main;
  main.Start();
}

void Main::Start()
{
  cout << "=== Main Menu ===\n1: Settings\n2: Calibrate\n3: Start Detection\n";
  cout << "d: Depth Obstacle Detector\nt: Traffic Light Detector\ns: Stop Sign Detector\n";

  char in;

  do { 
    in = _getch();

    switch (in)
    {
    case 'd':
      TestDod();
      break;
    case 't':
      TestTld();
      break;
    case 's':
      TestSsd();
      break;
    }
  } while (in != 'q' || in != 'Q');

  system("pause");
  return;
}

void Main::LoadImage(string path)
{
    _image = cv::imread(path);

    if (_image.cols == 0 || _image.rows == 0) throw("could not open image.");
}

void Main::TestDod()
{
  DepthObstacleDetector dod(_params._depthObstacleParams);
  
  string names[] = { "DepthMap.png" };
 
  for (int i = 0; i < 1; ++i)
  {
    LoadImage(PATH + names[i]);
    dod.CalculateRegionDepth(_image);
  }
}

void Main::TestTld()
{
  string names[] = { "tlight2.jpg", "tlight3.jpg", "tlight4.jpg", "tlight5.jpg" };

  _params._streetLightParams._mode = StreetLightParams::BlobDetectorMode;

  TrafficLightDetector tld(_params._streetLightParams);

  for (int i = 0; i < 4; ++i)
  {
    LoadImage(PATH + names[i]);
    tld.DetectTrafficLight(_image);
  }
}

void Main::TestSsd()
{
  StopSignDetector ssd();


}


