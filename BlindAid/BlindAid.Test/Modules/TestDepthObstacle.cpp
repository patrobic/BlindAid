#include "TestHelper.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CLASS "TestDepthObstacle"

namespace UnitTest
{
  TEST_CLASS(TestDepthObstacle)
  {
  public:
    TestHelper _testHelper;
    
    void Setup(int numImages, bool display = false)
    {
      _testHelper.params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(numImages);

      _testHelper.modes.DisableColor();
      _testHelper.modes.SetConsecutiveCount(vector<string>{"1"});

      if (display)
      {
        _testHelper.modes.EnableDisplay();
        _testHelper.params.GetDisplayParams()->SetMode(Mode::Realtime);
      }
    }
    
    TEST_METHOD(DepthObstacle10Test)
    {
      Setup(10);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacle100Test)
    {
      Setup(100);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacleDisplay10Test)
    {
      Setup(10, true);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }

    TEST_METHOD(DepthObstacleDisplay100Test)
    {
      Setup(100, true);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }
  };
}