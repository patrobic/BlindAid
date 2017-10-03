#include "ModuleVision.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

void Vision::Init(Data *data)
{
  _data = data;

  _dod.Init(&_data->_params, &_data->_currentDepthImage, &_data->_results);
  _tld.Init(&_data->_params, &_data->_currentColorImage, &_data->_results);
  _ssd.Init(&_data->_params, &_data->_currentColorImage, &_data->_results);
}

void Vision::operator()()
{
  // TODO: move thread creation to init, simply set _run bool flag to true in here.
  _data->_visionThread = thread(&Vision::VisionThread, this);
}

void Vision::VisionThread()
{
  int frame = 0;

  do
  {
    if (_data->_newFrameForVision)
    {
      if (_data->_bufferMutex.try_lock())
      {
        frame++;

        _data->_currentColorImage = _data->_colorImage.clone();
        _data->_currentDepthImage = _data->_depthImage.clone();
        _data->_bufferMutex.unlock();
        _data->_newFrameForVision = false;

        steady_clock::time_point start = steady_clock::now();
        _data->_resultMutex.lock();
        _ssd();
        _tld();
        _dod();
        _data->_resultMutex.unlock();
        steady_clock::time_point end = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(end - start);
        _data->_newFrameForControl = true;
        _data->_newFrameForDisplay = true;

        cout << "[VISION] Frame " << to_string(frame) << " process time : " << time_span.count() * 1000 << "ms.\n";
      }
    }
    this_thread::sleep_for(milliseconds(33));
  } 
  while (!_data->_captureDone || _data->_newFrameForVision);

  _data->_visionDone = true;
}

