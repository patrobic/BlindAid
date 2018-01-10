#include "Record.h"

#include <chrono>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

using namespace std;
using namespace std::chrono;
using namespace cv;

namespace Record
{
  Record::Record(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {

  }

  void Record::CreateFolder()
  {
    if (_firstRun)
    {
      time_t t = time(0);
      struct tm now;
      localtime_s(&now, &t);

      _folderName = to_string(now.tm_year + 1900) + '-' + to_string(now.tm_mon + 1) + '-' + to_string(now.tm_mday)
        + '_' + to_string(now.tm_hour) + '-' + to_string(now.tm_min) + '-' + to_string(now.tm_sec);

      string path = _params->GetPath() + "\\" + _folderName;
      system(("mkdir " + path).c_str());

      if (!(GetFileAttributesA(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY))
        throw exception("failed to create Record directory.");

      _firstRun = false;
    }
  }

  void Record::Process()
  {
    steady_clock::time_point start = steady_clock::now();

    CreateFolder();
    SaveToDisk();

    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    cout << "[RECORD ] Frame recorded (" << time_span.count() * 1000 << "ms).\n";
  }

  void Record::SaveToDisk()
  {
    if (_kbhit())
    {
      if (_params->GetType() == Parameters::Type::Color || _params->GetType() == Parameters::Type::Both)
      {
        imwrite(_params->GetPath() + "\\" + _folderName + "\\color_" + to_string(_index) + ".png", *_output->GetColorImage());
        imwrite(_params->GetPath() + "\\" + _folderName + "\\colorOverlay_" + to_string(_index) + ".png", *_input->GetColorOverlayImage());
      }

      if (_params->GetType() == Parameters::Type::Depth || _params->GetType() == Parameters::Type::Both)
      {
        imwrite(_params->GetPath() + "\\" + _folderName + "\\depth_" + to_string(_index) + ".png", *_output->GetDepthImage());
        imwrite(_params->GetPath() + "\\" + _folderName + "\\depthOverlay_" + to_string(_index) + ".png", *_input->GetDepthOverlayImage());
      }
      ++_index;

      _getch();
    }
  }
}