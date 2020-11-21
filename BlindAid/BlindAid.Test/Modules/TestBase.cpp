#include "TestBase.h"

UnitTest::TestBase::TestBase() :
  logger(&stream, &level),
  global(std::vector<std::string>(), ""),
  params(&global),
  modes(&params, &logger),
  results(&params)
{
  path = std::experimental::filesystem::current_path().string();

  global.SetMenuEnabled(false);

  modes.SimulateMode(std::vector<std::string>{ path + SOURCE });

  params.GetVisionParams()->GetTrafficLightParams()->GetDeepLearningParams()->SetModelPath(path + MODEL);
}

bool UnitTest::TestBase::AreStringsEqual(std::string className, std::string fileName)
{
  std::string result = stream.str();

  std::ifstream input(path + REFERENCE + "\\" + fileName);
  if (input)
  {
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::string expected = buffer.str();

    if (result == expected)
    {
      return true;
    }
    else
    {
      std::experimental::filesystem::create_directory(path + RESULT);

      std::ofstream output(path + RESULT + "\\" + fileName);
      output << result;
      output.close();

      return false;
    }
  }
  else
  {
    std::experimental::filesystem::create_directory(path + REFERENCE);

    std::ofstream output(path + REFERENCE + "\\" + fileName);
    output << result;
    output.close();

    return true;
  }
}
