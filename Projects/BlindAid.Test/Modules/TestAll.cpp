#include "TestHelper.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CLASS "TestAll"

namespace UnitTest
{
  TEST_CLASS(TestAll)
  {
  public:
    TestHelper _testHelper;

    void Setup(int numImages, bool display = false)
    {
      _testHelper.params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(numImages);

      if (display)
      {
        _testHelper.modes.EnableDisplay();
        _testHelper.params.GetDisplayParams()->SetMode(Mode::Realtime);
      }
    }

    TEST_METHOD(Global10Test)
    {
      Setup(10);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }

    TEST_METHOD(Global100Test)
    {
      Setup(100);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }

    TEST_METHOD(GlobalDisplay10Test)
    {
      Setup(10, true);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }

    TEST_METHOD(GlobalDisplay100Test)
    {
      Setup(100, true);

      _testHelper.RunCore();

      bool pass = _testHelper.AreStringsEqual(CLASS, string(__func__));
      Assert::IsTrue(pass);
    }
  };
}