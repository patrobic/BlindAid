#include "TestBase.h"

using namespace std;
using namespace cv;
using namespace experimental::filesystem;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CLASS "TestDepthObstacle"

namespace UnitTest
{
  TEST_CLASS(TestDepthObstacle), public TestBase
  {
  public:
    TEST_METHOD(DepthObstacle10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      modes.DisableColor();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacle100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.DisableColor();
      modes.SetConsecutiveCount(vector<string>{"1"});

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
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

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
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

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }
  };
}