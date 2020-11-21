#include "TestHelper.h"

using namespace std;
using namespace experimental::filesystem;

UnitTest::TestHelper::TestHelper() :
  logger(&stream, &level),
  global(vector<string>(), ""),
  params(&global),
  modes(&params, &logger),
  results(&params)
{
  path = current_path().string();

  global.SetMenuEnabled(false);

  modes.SimulateMode(vector<string>{ path + SOURCE });

  params.GetVisionParams()->GetTrafficLightParams()->GetDeepLearningParams()->SetModelPath(path + MODEL);
}

void UnitTest::TestHelper::RunCore()
{
  Core::Core core(&params, NULL, &results, &logger);
  core();
}

bool UnitTest::TestHelper::AreStringsEqual(string className, string fileName)
{
  string relPath = "\\" + className + "\\" + fileName + ".txt";

  string result = stream.str();

  ifstream input(path + REFERENCE + relPath);
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
      create_directories(path + RESULT + "\\" + className);

      ofstream output(path + RESULT + relPath);
      output << result;
      output.close();

      return false;
    }
  }
  else
  {
    create_directories(path + REFERENCE + "\\" + className);

    ofstream output(path + REFERENCE + relPath);
    output << result;
    output.close();

    return true;
  }
}
