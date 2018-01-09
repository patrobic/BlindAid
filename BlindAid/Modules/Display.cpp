#include "Display.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Display
{
  Display::Display(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {

  }

  void Display::Process()
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
    _input->GetCurrentDepthImage()->convertTo(*_input->GetDepthOverlayImage(), CV_8UC1, 1.f / 8.f, -0.5 / 8.f); // , 255.0 / (5 - 0.5));
    if (_input->GetDepthOverlayImage()->channels() == 1)
      cvtColor(*_input->GetDepthOverlayImage(), *_input->GetDepthOverlayImage(), CV_GRAY2BGR);

    Rect rect;
    for (int j = 0; j < VERT_REGIONS; ++j)
    {
      for (int i = 0; i < HORZ_REGIONS; ++i)
    {
        rect = _input->GetDepthObstacleResults()->GetRegionBounds(j, i);
        rectangle(*_input->GetDepthOverlayImage(), rect, Scalar(0, 0, 255), 2);
        putText(*_input->GetDepthOverlayImage(), to_string(_input->GetDepthObstacleResults()->GetRegionIntensity(j, i)), Point(rect.x + (int)(0.5 * rect.width) - 25, rect.y + (int)(0.5 * rect.height)), FONT_HERSHEY_PLAIN, 1.25, Scalar(0, 0, 255), 2);
      }

      (*_input->GetDepthOverlayImage())(cv::Rect(j * 60, 0, 60, 30)).setTo((int)_input->GetDepthObstacleResults()->GetVibrationIntensity()[j]->Get());
      putText(*_input->GetDepthOverlayImage(), to_string((int)_input->GetDepthObstacleResults()->GetVibrationIntensity()[j]->Get()), Point(j * 60 + 7, 22), FONT_HERSHEY_PLAIN, 1.5, (int)_input->GetDepthObstacleResults()->GetVibrationIntensity()[j]->Get() > 127 ? Scalar(0, 0, 0) : Scalar(255, 255, 255), 2);
    }
  }

  void Display::DrawTrafficLights()
  {
    _input->GetCurrentColorImage()->copyTo(*_input->GetColorOverlayImage());

    Scalar color[4] = { Scalar(0, 0, 255), Scalar(0, 255, 0), Scalar(0, 255, 255), Scalar(255, 0, 0) };
    string name[4] = { "Red", "Green", "Yellow", "None" };

    vector<Vision::TrafficLight::Result> result = _input->GetTrafficLightResults()->Get();

    if (result.size() == 1 && result.at(0)._center == Point(0, 0))
    {
      (*_input->GetColorOverlayImage())(cv::Rect(480, 0, 240, 60)).setTo(Scalar(255, 255, 255));
      putText(*_input->GetColorOverlayImage(), name[result.at(0)._color], Point(500, 45), FONT_HERSHEY_PLAIN, 3, color[result.at(0)._color], 2);

      for (int j = 0; j < 4; ++j)
      {
        (*_input->GetColorOverlayImage())(cv::Rect(j * 120, 0, 120, 60)).setTo(color[j] * max(0.25f, result.at(0)._confidence[j]));
        putText(*_input->GetColorOverlayImage(), to_string(result.at(0)._confidence[j]).substr(0, 4), Point(j * 120 + 10, 45), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255), 2);
      }
    }
    else
      for (int i = 0; i < result.size(); ++i)
      {
        circle(*_input->GetColorOverlayImage(), result.at(i)._center, (int)result.at(i)._radius + 2, color[result.at(i)._color], 2);
        putText(*_input->GetColorOverlayImage(), name[result.at(i)._color] + "TrafficLight" + to_string(i), Point(result.at(i)._center.x - (int)result.at(i)._radius, result.at(i)._center.y - (int)result.at(i)._radius), FONT_HERSHEY_PLAIN, 1, color[result.at(i)._color]);
      }
  }

  void Display::DrawStopSign()
  {
    Vision::StopSign::Data result = *_input->GetStopSignResults();
    circle(*_input->GetColorOverlayImage(), result.GetRegion()._center, (int)result.GetRegion()._radius + 2, Scalar(0, 255, 255));
    putText(*_input->GetColorOverlayImage(), "StopSign", Point(result.GetRegion()._center.x - (int)result.GetRegion()._radius, result.GetRegion()._center.y - (int)result.GetRegion()._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
  }

  void Display::DisplayImage()
  {
    if (_input->GetColorOverlayImage()->rows > 0 && _input->GetColorOverlayImage()->cols > 0)
    {
      namedWindow("Color Image", WINDOW_NORMAL);
      moveWindow("Color Image", _params->GetColorWindowPosition().x, _params->GetColorWindowPosition().y);
      resizeWindow("Color Image", (int)(_input->GetColorOverlayImage()->cols * _params->GetColorWindowScale()), (int)(_input->GetColorOverlayImage()->rows * _params->GetColorWindowScale()));
      imshow("Color Image", *_input->GetColorOverlayImage());
      waitKey(1);
    }

    if (_input->GetCurrentDepthImage()->rows > 0 && _input->GetCurrentDepthImage()->cols > 0)
    {
      namedWindow("Depth Image", WINDOW_NORMAL);
      moveWindow("Depth Image", _params->GetDepthWindowPosition().x, _params->GetDepthWindowPosition().y);
      resizeWindow("Depth Image", (int)(_input->GetDepthOverlayImage()->cols * _params->GetDepthWindowScale()), (int)(_input->GetDepthOverlayImage()->rows * _params->GetDepthWindowScale()));
      imshow("Depth Image", *_input->GetDepthOverlayImage());
      waitKey(1);
    }
  }
}