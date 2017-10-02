#include "Main.h"
#include <conio.h>

#define PATH "C:\\Projects\\BlindAid\\TestImages\\"

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

void Main::LoadImage(string path)
{
    _image = cv::imread(path);

    if (_image.cols == 0 || _image.rows == 0) throw("could not open image.");
}

void Main::TestDod()
{
  string names[] = { "DepthMap.png" };
 
  for (int i = 0; i < 1; ++i)
  {
    LoadImage(PATH + names[i]);
    _dod.Start();

    cv::imshow("DepthObstacleDetector Results", _image);
    cv::waitKey();
  }
  cvDestroyWindow("DepthObstacleDetector Results");
}

void Main::TestTld()
{
  string names[] = { "tlight2.jpg", "tlight3.jpg", "tlight4.jpg", "tlight5.jpg" };

  for (int i = 0; i < 4; ++i)
  {
    LoadImage(PATH + names[i]);
    _tld.Start();

    cv::imshow("TrafficLightDetector Results", _image);
    cv::waitKey();
  }
  cvDestroyWindow("TrafficLightDetector Results");
}

void Main::TestSsd()
{
  for (int i = 1; i < 8; ++i)
  {
    LoadImage(PATH + string("stop") + std::to_string(i) + string(".jpg"));
    _ssd.Start();

    cv::imshow("StopSignDetector Results", _image);
    cv::waitKey();
  }
  cvDestroyWindow("StopSignDetector Results");
}

void Main::TestVideo()
{
  string sample = "TrafficLight.mp4";

  for (int i = 0; i < 4; ++i)
  {
    _core.Simulate(true, PATH + sample);
    //_core.Simulate(PATH + string("tlight") + std::to_string(i) + string(".avi"));
  }
}

void Main::TestPhoto()
{
  string sample = "DepthMap.png";

  _core.Simulate(false, PATH + sample);
}