#include "ModuleDisplay.h"

using namespace std;
using namespace cv;

void Display::Init(Data *data, IParameters *params, IResults *input, IResults *output)
{
  _data = data;
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Vision::Results*>(input);
  _output = static_cast<Results*>(output);
}

void Display::operator()()
{
  _data->_displayThread = thread(&Display::DisplayThread, this);
}

void Display::ShowDepthObstacles()
{
  Rect rect;
  for (int i = 0; i < HORZ_REGIONS; ++i)
  {
    for (int j = 0; j < VERT_REGIONS; ++j)
    {
      rect = _input->GetDepthObstacleResults()->GetRegionBounds(j, i);
      rectangle(*_input->GetCurrentDepthImage(), rect, Scalar(0, 0, 255), 2);
      putText(*_input->GetCurrentDepthImage(), to_string(_input->GetDepthObstacleResults()->GetRegionIntensity(j, i)), Point(rect.x + 0.5 * rect.width, rect.y + 0.5 * rect.height), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    }
  }
}

void Display::ShowTrafficLights()
{
  DetectTrafficLight::Results result = *_input->GetTrafficLightResults();

  for (int i = 0; i < _input->GetTrafficLightResults()->Size(); ++i)
  {
    circle(*_input->GetCurrentColorImage(), result.At(i)._center, (int)result.At(i)._radius + 2, Scalar(0, 255, 255), 2);
    putText(*_input->GetCurrentColorImage(), "TrafficLight" + to_string(i), Point(result.At(i)._center.x - result.At(i)._radius, result.At(i)._center.y - result.At(i)._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
  }
}

void Display::ShowStopSign()
{
  DetectStopSign::Results result = *_input->GetStopSignResults();
  circle(*_input->GetCurrentColorImage(), result.GetRegion()._center, result.GetRegion()._radius + 2, Scalar(0, 255, 255));
  putText(*_input->GetCurrentColorImage(), "StopSign", Point(result.GetRegion()._center.x - result.GetRegion()._radius, result.GetRegion()._center.y - result.GetRegion()._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
}

void Display::DisplayImage()
{
  namedWindow("Color Image");
  moveWindow("Color Image", 20, 20);
  imshow("Color Image", *_input->GetCurrentColorImage());
  waitKey(1);

  namedWindow("Depth Image");
  moveWindow("Depth Image", 800, 20);
  imshow("Depth Image", *_input->GetCurrentDepthImage());
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
  }
  while (!_data->_visionDone || _data->_newFrameForDisplay);
}