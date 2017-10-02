#include "ModuleDisplay.h"

#include  "IModule.h"
#include "Settings.h"

void Display::Init(Data *data, std::thread *thread)
{
  _data = data;
  _thread = thread;
}

void Display::Start()
{
  // TODO: MAJOR!! Not yet thread safe!! Implement thread like other modules
  ShowDepthObstacles();
  ShowTrafficLights();
  ShowStopSign();

  namedWindow("Color Image");
  moveWindow("Color Image", 20, 20);
  imshow("Color Image", _data->_currentColorImage);
  waitKey(1);

  namedWindow("Depth Image");
  moveWindow("Depth Image", 800, 20);
  imshow("Depth Image", _data->_currentDepthImage);
  waitKey(1);
}

void Display::ShowDepthObstacles()
{
  int width = _data->_currentDepthImage.cols / COL_REGIONS;
  int height = _data->_currentDepthImage.rows / ROW_REGIONS;

  for (int i = 0; i < ROW_REGIONS; ++i)
  {
    for (int j = 0; j < COL_REGIONS; ++j)
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
  circle(_data->_currentColorImage, result.GetPoint(), result.GetSize() + 2, Scalar(0, 255, 255));
  putText(_data->_currentColorImage, "StopSign", Point(result.GetPoint().x - result.GetSize(), result.GetPoint().y - result.GetSize()), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
}

void Display::DisplayT()
{
}