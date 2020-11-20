#include "CppUnitTest.h"

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <opencv2/core/types.hpp>
#include <CoreParameters.h>
#include <CoreData.h>
#include <Core.h>
#include "IParameters.h"
#include "../../BlindAid.Driver/Menu/Modes.h"
#include "Logger.h"

using namespace std;
using namespace cv;
using namespace experimental::filesystem;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define PATH "\\..\\..\\..\\Data\\Test\\Sample"
#define MODEL "\\..\\..\\Resources\\MachineLearning"
#define RESULT "\\..\\..\\..\\Data\\Test\\Result"
#define REFERENCE "\\..\\..\\..\\Data\\Test\\Reference"

namespace UnitTest
{
  TEST_CLASS(TestGlobal)
  {
  public:
    Tools::LogLevel level = Tools::LogLevel::Warning;
    Tools::Logger logger;

    GlobalParameters global;
    Core::CoreParameters params;

    Modes modes;

    Core::CoreData results;

    string path;

    std::stringstream stream;

    TestGlobal() :
      logger(&stream, &level),
      global(vector<string>(), ""),
      params(&global),
      modes(&params, &logger),
      results(&params)
    {
      path = current_path().string();

      global.SetMenuEnabled(false);

      modes.SimulateMode(vector<string>{ path + PATH });

      params.GetVisionParams()->GetTrafficLightParams()->GetDeepLearningParams()->SetModelPath(path + MODEL);
    }

    TEST_METHOD(Global10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);
      
      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(Global100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(GlobalDisplay10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);
      
      modes.EnableDisplay();
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(GlobalDisplay100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.EnableDisplay();
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(TrafficLight10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      modes.DisableDepth();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(TrafficLight100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.DisableDepth();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(TrafficLightDisplay10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      modes.DisableDepth();
      modes.EnableDisplay();
      modes.SetConsecutiveCount(vector<string>{"1"});
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(TrafficLightDisplay100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.DisableDepth();
      modes.EnableDisplay();
      modes.SetConsecutiveCount(vector<string>{"1"});
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacle10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      modes.DisableColor();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacle100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.DisableColor();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacleDisplay10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      modes.DisableColor();
      modes.EnableDisplay();
      modes.SetConsecutiveCount(vector<string>{"1"});
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacleDisplay100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.DisableColor();
      modes.EnableDisplay();
      modes.SetConsecutiveCount(vector<string>{"1"});
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    bool AreStringsEqual(string fileName)
    {
      string result = stream.str();

      ifstream input(path + REFERENCE + "\\" + fileName);
      if (input)
      {
        stringstream buffer;
        buffer << input.rdbuf();
        input.close();

        string expected = buffer.str();

        if (result == expected)
        {
          return true;
        }
        else
        {
          create_directory(path + RESULT);

          ofstream output(path + RESULT + "\\" + fileName);
          output << result;
          output.close();

          return false;
        }
      }
      else
      {
        create_directory(path + REFERENCE);

        ofstream output(path + REFERENCE + "\\" + fileName);
        output << result;
        output.close();

        return true;
      }
    }
  };
}