#include "TestBase.h"

using namespace std;
using namespace cv;
using namespace experimental::filesystem;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CLASS "TestAll"

namespace UnitTest
{
  TEST_CLASS(TestAll), public TestBase
  {
  public:
    TestAll()
    {
    }

    TEST_METHOD(Global10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(Global100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(GlobalDisplay10Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(10);

      modes.EnableDisplay();
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }

    TEST_METHOD(GlobalDisplay100Test)
    {
      params.GetCaptureParams()->GetSimulateParams()->SetEndIndex(100);

      modes.EnableDisplay();
      params.GetDisplayParams()->SetMode(Mode::Realtime);

      Core::Core core(&params, NULL, &results, &logger);
      core();

      bool pass = AreStringsEqual(CLASS, string(__func__) + ".txt");
      Assert::IsTrue(pass);
    }
  };
}