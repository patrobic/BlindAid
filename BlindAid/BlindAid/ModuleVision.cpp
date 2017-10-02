#include "ModuleVision.h"

void Vision::Init(Data *data, std::thread *thread)
{
  _data = data;
  _thread = thread;

  _dod.Init(&_data->_params, &_data->_currentDepthImage, &_data->_results);
  _tld.Init(&_data->_params, &_data->_currentColorImage, &_data->_results);
  _ssd.Init(&_data->_params, &_data->_currentColorImage, &_data->_results);
}

void Vision::Start()
{
  *_thread = thread(&Vision::TVision, this);
}

void Vision::DisplayImage(int frame, double time)
{
  cout << "[VISION] Frame " << to_string(frame) << " process time : " << time * 1000 << "ms.\n";

  namedWindow("Video Results");
  imshow("Video Results", _data->_colorImage);
  waitKey(1);
}

void Vision::TVision()
{
  int frame = 0;

  do
  {
    if (_data->_newCapturedFrame)
    {
      if (_data->_bufferMutex.try_lock())
      {
        frame++;

        _data->_currentColorImage = _data->_colorImage.clone();
        _data->_currentDepthImage = _data->_depthImage.clone();
        _data->_bufferMutex.unlock();
        _data->_newCapturedFrame = false;

        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
        _data->_resultMutex.lock();
        _ssd.Start();
        _tld.Start();
        _dod.Start();
        _data->_resultMutex.unlock();
        chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);
        _data->_newProcessedFrame = true;

        DisplayImage(frame, time_span.count());
      }
    }
    this_thread::sleep_for(std::chrono::milliseconds(33));
  } 
  while (!_data->_captureDone || _data->_newCapturedFrame);

  _data->_visionDone = true;
}

