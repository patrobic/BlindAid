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
  _dod.Init(&_params._depthObstacleParams, &_image, &_dodResults);
 
  _params._streetLightParams.SetMode(TrafficLightParams::BlobDetectorMode);
  _tld.Init(&_params._streetLightParams, &_image, &_tldResults);

  _ssd.Init(&_params._stopSignParams, &_image, &_ssdResults);
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
    case 'v':
      TestVideo();
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
    //_cap.open(PATH + string("tlight") + std::to_string(i) + string(".avi"));
    _cap.open(PATH + sample);

    _processingActive = true;
    thread loadVideo(&Main::TLoadVideo, this);
    thread processFrames(&Main::TProcessFrames, this);

    loadVideo.join();
    processFrames.join();
  }
}

void Main::TLoadVideo()
{
  int frame = 0;
  while (_processingActive)
  {
    frame++;
    _bufferMutex.lock();
    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
    _processingActive = _cap.read(_image);
    chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);

    cout << "Frame " << to_string(frame) << " load time : " << time_span.count()*1000 << "ms.\n";

    _bufferMutex.unlock();
    this_thread::sleep_for(std::chrono::milliseconds(33));
  }

  _processingActive = false;
}

void Main::TProcessFrames()
{
  int frame = 0;
  while (_processingActive)
  {
    if (_bufferMutex.try_lock())
    {
      frame++;
      _currentImage = _image.clone();
      _bufferMutex.unlock();

      chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
      _ssd.Start();
      _tld.Start();
      _dod.Start();
      chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
      chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);

      cout << "Frame " << to_string(frame) << " process time : " << time_span.count() * 1000 << "ms.\n";

      cv::imshow("Video Results", _image);
      cv::waitKey(1);
      this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }
}
