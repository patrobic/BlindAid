#include "CppUnitTest.h"

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
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
    Core::Core core;

    string path;

    TestGlobal() :
      logger(&level),
      global(vector<string>(), ""),
      params(&global),
      modes(&params, &logger),
      results(&params),
      core(&params, NULL, &results, &logger)
    {
      path = current_path().string();

      params.GetVisionParams()->GetTrafficLightParams()->GetDeepLearningParams()->SetModelPath(path + MODEL);
      global.SetMenuEnabled(false);
      modes.SimulateMode(vector<string>{ path + PATH });
    }

    TEST_METHOD(GlobalTest)
    {
      core();
    }

    TEST_METHOD(TrafficLightTest)
    {
      modes.DisableDepth();
      modes.EnableDisplay();
     // modes.LowPerformance();
      modes.SetConsecutiveCount(vector<string>{"1"});
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      core();
    }

    TEST_METHOD(DepthObstacleTest)
    {
      modes.DisableColor();
      // modes.EnableDisplay();
      // modes.LowPerformance();
      modes.SetConsecutiveCount(vector<string>{"1"});
      // params.GetDisplayParams()->SetMode(Mode::Realtime);

      core();
    }
  };
}