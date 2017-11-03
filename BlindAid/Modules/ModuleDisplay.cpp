#include "ModuleDisplay.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

Display::Display(IParameters *params, IData *input, IData *output)
{
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Vision::Data*>(input);
  _output = static_cast<Data*>(output);
}

void Display::operator()()
{
  steady_clock::time_point start = steady_clock::now();

  DrawDepthObstacles();
  DrawTrafficLights();
  DrawStopSign();
  DisplayImage();

  steady_clock::time_point end = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(end - start);

  cout << "[DISPLAY] Frame displayed (" << time_span.count() * 1000 << "ms).\n";
}

void Display::DrawDepthObstacles()
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

void Display::DrawTrafficLights()
{
  DetectTrafficLight::Data result = *_input->GetTrafficLightResults();

  for (int i = 0; i < _input->GetTrafficLightResults()->Size(); ++i)
  {
    circle(*_input->GetCurrentColorImage(), result.At(i)._center, (int)result.At(i)._radius + 2, Scalar(0, 255, 255), 2);
    putText(*_input->GetCurrentColorImage(), "TrafficLight" + to_string(i), Point(result.At(i)._center.x - result.At(i)._radius, result.At(i)._center.y - result.At(i)._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
  }
}

void Display::DrawStopSign()
{
  DetectStopSign::Data result = *_input->GetStopSignResults();
  circle(*_input->GetCurrentColorImage(), result.GetRegion()._center, result.GetRegion()._radius + 2, Scalar(0, 255, 255));
  putText(*_input->GetCurrentColorImage(), "StopSign", Point(result.GetRegion()._center.x - result.GetRegion()._radius, result.GetRegion()._center.y - result.GetRegion()._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
}

void Display::DisplayImage()
{
  namedWindow("Color Image");
  moveWindow("Color Image", 20, 20);
  imshow("Color Image", *_input->GetCurrentColorImage());
  waitKey(1);

  if (_input->GetCurrentDepthImage()->rows > 0 && _input->GetCurrentDepthImage()->cols > 0)
  {
    namedWindow("Depth Image");
    moveWindow("Depth Image", 800, 20);
    imshow("Depth Image", *_input->GetCurrentDepthImage());
    waitKey(1);
  }
}