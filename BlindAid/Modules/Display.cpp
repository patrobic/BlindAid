#include "Display.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Display
{
  Display::Display(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {
    _depthOverlay = Mat(Size(628, 468), CV_8UC3);
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
    _input->GetCurrentDepthImage()->convertTo(_depthOverlay, CV_8UC1, 1.f / 8.f, -0.5 / 8.f); // , 255.0 / (5 - 0.5));
    cvtColor(_depthOverlay, _depthOverlay, CV_GRAY2BGR);

    Rect rect;
    for (int i = 0; i < HORZ_REGIONS; ++i)
    {
      for (int j = 0; j < VERT_REGIONS; ++j)
      {
        rect = _input->GetDepthObstacleResults()->GetRegionBounds(j, i);
        rectangle(_depthOverlay, rect, Scalar(0, 0, 255), 2);
        putText(_depthOverlay, to_string(_input->GetDepthObstacleResults()->GetRegionIntensity(j, i)), Point(rect.x + (int)(0.5 * rect.width) - 20, rect.y + (int)(0.5 * rect.height)), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
      }
    }
  }

  void Display::DrawTrafficLights()
  {
    vector<Vision::TrafficLight::Result> result = _input->GetTrafficLightResults()->Get();

    for (int i = 0; i < result.size(); ++i)
    {
      Scalar color[3] = { Scalar(0, 0, 255), Scalar(0, 255, 0), Scalar(0, 255, 255) };
      string name[3] = { "Red", "Green", "Yellow" };

      circle(*_input->GetCurrentColorImage(), result.at(i)._center, (int)result.at(i)._radius + 2, color[result.at(i)._color], 2);
      putText(*_input->GetCurrentColorImage(), name[result.at(i)._color] + "TrafficLight" + to_string(i), Point(result.at(i)._center.x - (int)result.at(i)._radius, result.at(i)._center.y - (int)result.at(i)._radius), FONT_HERSHEY_PLAIN, 1, color[result.at(i)._color]);
    }
  }

  void Display::DrawStopSign()
  {
    Vision::StopSign::Data result = *_input->GetStopSignResults();
    circle(*_input->GetCurrentColorImage(), result.GetRegion()._center, (int)result.GetRegion()._radius + 2, Scalar(0, 255, 255));
    putText(*_input->GetCurrentColorImage(), "StopSign", Point(result.GetRegion()._center.x - (int)result.GetRegion()._radius, result.GetRegion()._center.y - (int)result.GetRegion()._radius), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255));
  }

  void Display::DisplayImage()
  {
    if (_input->GetCurrentColorImage()->rows > 0 && _input->GetCurrentColorImage()->cols > 0)
    {
      namedWindow("Color Image");
      moveWindow("Color Image", _params->GetColorWindowPosition().x, _params->GetColorWindowPosition().y);
      resizeWindow("Color Image", (int)(_input->GetCurrentColorImage()->cols * _params->GetColorWindowScale()), (int)(_input->GetCurrentColorImage()->rows * _params->GetColorWindowScale()));
      imshow("Color Image", *_input->GetCurrentColorImage());
      waitKey(1);
    }

    if (_input->GetCurrentDepthImage()->rows > 0 && _input->GetCurrentDepthImage()->cols > 0)
    {
      //cv::Mat mat = cv::Mat(628, 468, CV_8UC1);
      //(*_input->GetCurrentDepthImage())(Rect(0, 0, 628, 468)).convertTo(mat, CV_8UC1, 1.f / 8.f, -0.5/8.f); // , 255.0 / (5 - 0.5));

      namedWindow("Depth Image");
      moveWindow("Depth Image", _params->GetDepthWindowPosition().x, _params->GetDepthWindowPosition().y);
      resizeWindow("Depth Image", (int)(_depthOverlay.cols * _params->GetDepthWindowScale()), (int)(_depthOverlay.rows * _params->GetDepthWindowScale()));
      imshow("Depth Image", _depthOverlay);
      waitKey(1);
    }
  }
}