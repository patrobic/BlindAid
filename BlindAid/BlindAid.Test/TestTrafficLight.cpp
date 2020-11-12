#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Modules\Core.h"

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace cv;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define PATH "C:\\Projects\\BlindAid\\TestData\\"

namespace UnitTest
{
  TEST_CLASS(TestTrafficLight)
  {
  public:
    struct TestData
    {
      TestData(string colorPath, string depthPath, vector<Point> points)
      {
        _colorPath = colorPath;
        _depthPath = depthPath;
        _points = points;
      }

      string _colorPath;
      string _depthPath;
      vector<Point> _points;

      vector<int> _distance;
    };

    TEST_METHOD(MultipleImages)
    {
      float maxDeviation = 10;

      vector<TestData> testData =
      {
        TestData("TrafficLight\\tlight1.jpg", "depthMap.png", vector<Point>{ Point(312, 127), Point(429, 145), Point(596, 225), Point(719, 97) }),
        TestData("TrafficLight\\tlight2.jpg", "depthMap.png", vector<Point>{ Point(270, 56), Point(338, 52) }),
        TestData("TrafficLight\\tlight3.jpg", "depthMap.png", vector<Point>{ }),
        TestData("TrafficLight\\tlight4.jpg", "depthMap.png", vector<Point>{ Point(1388, 595), Point(1570, 586) }),
        TestData("TrafficLight\\tlight5.jpg", "depthMap.png", vector<Point>{ Point(51, 344), Point(664, 277), Point(948, 415) }),
        TestData("TrafficLight\\tlight6.jpg", "depthMap.png", vector<Point>{ Point(435, 260), Point(888, 437) }),
        TestData("TrafficLight\\tlight7.jpg", "depthMap.png", vector<Point>{ Point(487, 304), Point(955, 487) }),
        TestData("TrafficLight\\tlight8.jpg", "depthMap.png", vector<Point>{ Point(277, 226), Point(836, 443) }),
        TestData("TrafficLight\\tlight9.jpg", "depthMap.png", vector<Point>{ Point(382, 274), Point(974, 407) }),
        TestData("TrafficLight\\tlight10.jpg", "depthMap.png", vector<Point>{ Point(320, 242), Point(913, 414) }),
        TestData("TrafficLight\\tlight11.jpg", "depthMap.png", vector<Point>{ Point(41, 474), Point(552, 332), Point(677, 338) }),
        TestData("TrafficLight\\tlight12.jpg", "depthMap.png", vector<Point>{ Point(165, 283), Point(368, 291), Point(662, 330), Point(994, 453) }),
        TestData("TrafficLight\\tlight13.jpg", "depthMap.png", vector<Point>{ Point(486, 264), Point(945, 440) }),
        TestData("TrafficLight\\tlight14.jpg", "depthMap.png", vector<Point>{ Point(84, 134), Point(201, 128), Point(392, 185), Point(495, 179) }),
        TestData("TrafficLight\\tlight15.jpg", "depthMap.png", vector<Point>{ Point(202, 76), Point(362, 61) }),
      };

      Core::Parameters params;
      params.GetCaptureParams()->SetMode(Simulate);
      params.GetControlParams()->SetMode(Simulate);
      params.GetVisionParams()->GetDepthObstacleParams()->SetToggle(SwitchableParameters::Toggle::Disabled);
      params.GetDisplayParams()->SetToggle(SwitchableParameters::Toggle::Enabled);
      params.GetVisionParams()->GetTrafficLightParams()->SetMode(Vision::TrafficLight::Parameters::Version::BlobDetector);
      params.GetVisionParams()->GetTrafficLightParams()->SetSmoothingCount(0);
      params.GetVisionParams()->GetTrafficLightParams()->SetCenterRegionRatio(1.f);
      params.GetVisionParams()->GetTrafficLightParams()->SetUpperRegionRatio(1.f);
      params.GetCaptureParams()->GetSimulateParams()->SetMediaType(Capture::Simulate::Parameters::MediaType::Photo);

      Core::Data results(&params);
      Core::Core core(&params, NULL, &results);

      for (int i = 0; i < testData.size(); ++i)
      {
        float score = 0;

        params.GetCaptureParams()->GetSimulateParams()->SetColorSimDataPath(PATH + testData.at(i)._colorPath);
        params.GetCaptureParams()->GetSimulateParams()->SetDepthSimDataPath(PATH + testData.at(i)._depthPath);
        core();

        vector<Vision::TrafficLight::Result> *tlResults = results.GetVisionResults()->GetTrafficLightResults()->GetAll();

        int countDiff = (int)testData.at(i)._points.size() -tlResults->size();
        Assert::IsTrue(abs(countDiff) <= 2); // ensure that detected number of lights is NOT more than expected (i.e. allow missing detections but not false detections).

        vector<float> distances;
        for (int j = 0; j < tlResults->size(); ++j)
          for (int k = 0; k < testData.at(i)._points.size(); ++k)
            distances.push_back((float)norm(testData.at(i)._points.at(k) - tlResults->at(j).GetCenter()));

        std::sort(distances.begin(), distances.end());

        stringstream ss;
        ss << fixed << setprecision(2) << "Test" << i << "(" << testData.at(i)._colorPath << "), ";
        for (int k = 0; k < std::min((int)tlResults->size(), (int)testData.at(i)._points.size()); ++k)
        {
          score += (1 - 0.01f * distances.at(k)) / std::max((int)tlResults->size(), (int)testData.at(i)._points.size());
          ss << "P" << k + 1 << "(" << distances.at(k) << "), ";
          Assert::IsTrue(distances.at(k) < maxDeviation);
        }

        if (testData.at(i)._points.size() == 0 && tlResults->size() == 0)
          score = 1.0f;

        Assert::IsTrue(score >= 0.6f);
        ss << "Score(" << score << "), Count(" << testData.at(i)._points.size() << "," << tlResults->size() << ").";
        Logger::WriteMessage(ss.str().c_str());
      }
    }
  };
}