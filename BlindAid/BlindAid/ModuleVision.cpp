#include "ModuleVision.h"

void Vision::Init(std::string path, std::thread *thread, std::mutex *bufferMutex, bool *processingActive, cv::Mat *image, VisionParams *params, VisionResults *results)
{
  _path = path;
  _thread = thread;
  _processingActive = processingActive;
  _bufferMutex = bufferMutex;
  _image = image;
  _params = params;
  _results = results;

  _dod.Init(_params, _image, _results);
  _tld.Init(_params, _image, _results);
  _ssd.Init(_params, _image, _results);
}

void Vision::Start()
{
  *_thread = thread(&Vision::TVision, this);
}

void Vision::TVision()
{
  int frame = 0;
  while (_processingActive)
  {
    if (_bufferMutex->try_lock())
    {
      frame++;
      _currentImage = _image->clone();
      _bufferMutex->unlock();

      chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
      _ssd.Start();
      _tld.Start();
      _dod.Start();
      chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
      chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);

      cout << "Frame " << to_string(frame) << " process time : " << time_span.count() * 1000 << "ms.\n";

      cv::imshow("Video Results", *_image);
      cv::waitKey(1);
      this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }
}