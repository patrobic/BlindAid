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

#define MODEL "\\..\\..\\Resources\\MachineLearning"

#define SOURCE "\\..\\..\\..\\Data\\Source"
#define RESULT "\\..\\..\\..\\Data\\Result"
#define REFERENCE "\\..\\..\\..\\Data\\Reference"

namespace UnitTest
{
  class TestBase
  {
  public:
    Tools::LogLevel level = Tools::LogLevel::Info;
    Tools::Logger logger;

    GlobalParameters global;
    Core::CoreParameters params;

    Modes modes;

    Core::CoreData results;

    std::string path;

    std::stringstream stream;

    TestBase();

  protected:

    bool AreStringsEqual(std::string className, std::string fileName);
  };
}