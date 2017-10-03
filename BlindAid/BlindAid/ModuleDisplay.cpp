#include "ModuleDisplay.h"

using namespace std;
using namespace cv;

void Display::Init(Data *data)
{
  _data = data;
}

void Display::operator()()
{
  _data->_displayThread = thread(&Display::DisplayThread, this);
}

void Display::ShowDepthObstacles()
{
  int width = _data->_currentDepthImage.cols / VERT_REGIONS;
  int height = _data->_currentDepthImage.rows / HORZ_REGIONS;

  for (int i = 0; i < HORZ_REGIONS; ++i)
  {
    for (int j = 0; j < VERT_REGIONS; ++j)
    {
      rectangle(_data->_currentDepthImage, Point(j * width, i * height), Point((j + 1) * width, (i + 1) * height), Scalar(0, 0, 255), 2);
      putText(_data->_currentDepthImage, to_string(_data->_results.GetDepthObstacleResults().GetMat().at<char>(i, j)), Point((j + 0.5) * width, (i + 0.5) * height), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    }
  }
}

void Display::ShowTrafficLights()
{
  TrafficLightResults result = _data->_results.GetTrafficLightResults();

  for (int i = 0; i < _data->_results.GetTrafficLightResults().Size(); ++i)
  {
    circle(_data->_currentColorImage, result.At(i)._center, (int)result.At(i)._radius + 2, Scalar(0, 255, 255), 2);
    putText(_data->_currentColorImage, "TrafficLight" + to_string(i), Point(result.At(i)._center.x - result.At(i)._radius, result.At(i)._center.y - result.At(i)._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
  }
}

void Display::ShowStopSign()
{
  StopSignResults result = _data->_results.GetStopSignResults();
  circle(_data->_currentColorImage, result.GetRegion()._center, result.GetRegion()._radius + 2, Scalar(0, 255, 255));
  putText(_data->_currentColorImage, "StopSign", Point(result.GetRegion()._center.x - result.GetRegion()._radius, result.GetRegion()._center.y - result.GetRegion()._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
}

void Display::DisplayImage()
{
  namedWindow("Color Image");
  moveWindow("Color Image", 20, 20);
  imshow("Color Image", _data->_currentColorImage);
  waitKey(1);

  namedWindow("Depth Image");
  moveWindow("Depth Image", 800, 20);
  imshow("Depth Image", _data->_currentDepthImage);
  waitKey(1);
}

void Display::DisplayThread()
{
  int frame = 0;

  do
  {
    if (_data->_newFrameForDisplay)
    {
      if (_data->_resultMutex.try_lock())
      {
        frame++;

        ShowDepthObstacles();
        ShowTrafficLights();
        ShowStopSign();
        DisplayImage();

        _data->_resultMutex.unlock();
        _data->_newFrameForDisplay = false;

        cout << "[DISPLAY] Frame " << to_string(frame) << " displayed.\n";
      }
    }
    this_thread::sleep_for(chrono::milliseconds(33));
  } while (!_data->_visionDone || _data->_newFrameForDisplay);
}