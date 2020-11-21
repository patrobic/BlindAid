#include "TestBase.h"

using namespace std;
using namespace cv;
using namespace experimental::filesystem;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CLASS "TestTrafficLight"

namespace UnitTest
{
  TEST_CLASS(TestTrafficLight), public TestBase
  {
  public:
    TEST_METHOD(TrafficLight10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      modes.DisableDepth();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(TrafficLight100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.DisableDepth();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
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

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
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

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }
  };
}