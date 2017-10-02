#include "ModuleVision.h"

void Vision::Init(std::thread *thread, std::mutex *bufferMutex, std::mutex *resultMutex, atomic_bool *captureDone, atomic_bool *visionDone, atomic_bool *newCapturedFrame, atomic_bool *newProcessedFrame, cv::Mat *image, VisionParams *params, VisionResults *results)
{
  _thread = thread;
  _captureDone = captureDone;
  _visionDone = visionDone;
  _newCapturedFrame = newCapturedFrame;
  _newProcessedFrame = newProcessedFrame;
  _bufferMutex = bufferMutex;
  _resultMutex = resultMutex;
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

void Vision::DisplayImage(int frame, double time)
{
  cout << "[VISION] Frame " << to_string(frame) << " process time : " << time * 1000 << "ms.\n";

  namedWindow("Video Results");
  imshow("Video Results", *_image);
  waitKey(1);
}

void Vision::TVision()
{
  int frame = 0;

  do
  {
    if (*_newCapturedFrame)
    {
      if (_bufferMutex->try_lock())
      {
        frame++;

        _currentImage = _image->clone();
        _bufferMutex->unlock();
        *_newCapturedFrame = false;

        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
        _resultMutex->lock();
        _ssd.Start();
        _tld.Start();
        _dod.Start();
        _resultMutex->unlock();
        chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);
        *_newProcessedFrame = true;

        DisplayImage(frame, time_span.count());
      }
    }
    this_thread::sleep_for(std::chrono::milliseconds(33));
  } 
  while (!*_captureDone || *_newCapturedFrame);

  *_visionDone = true;
}

