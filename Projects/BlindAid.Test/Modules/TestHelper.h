#pragma once

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

#define MODEL "\\..\\BlindAid.Resources\\MachineLearning"

#define SOURCE "\\..\\BlindAid.Data\\Source"
#define RESULT "\\..\\BlindAid.Data\\Result"
#define REFERENCE "\\..\\BlindAid.Data\\Reference"

namespace UnitTest
{
  class TestHelper
  {
  public:

    Tools::LogLevel level = Tools::LogLevel::Error;
    Tools::Logger logger;

    GlobalParameters global;
    Core::CoreParameters params;

    Modes modes;

    Core::CoreData results;

    std::string path;

    std::stringstream stream;

    TestHelper();

    void RunCore();

    bool AreStringsEqual(std::string className, std::string fileName);
  };
}