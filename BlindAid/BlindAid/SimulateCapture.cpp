#include "SimulateCapture.h"

void CaptureSim::Init(std::string path, std::thread *thread, std::mutex *bufferMutex, bool *processingActive, cv::Mat *image)
{
  _path = path;
  _thread = thread;
  _processingActive = processingActive;
  _bufferMutex = bufferMutex;
  _image = image;
}

void CaptureSim::Start()
{
  _cap.open(_path);

  *_processingActive = true;
  *_thread = thread(&CaptureSim::TCapture, this);
}

void CaptureSim::TCapture()
{
  int frame = 0;
  while (_processingActive)
  {
    frame++;
    _bufferMutex->lock();
    time_point<steady_clock> start = steady_clock::now();
    *_processingActive = _cap.read(*_image);
    time_point<steady_clock> end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    cout << "Frame " << to_string(frame) << " load time : " << time_span.count() * 1000 << "ms.\n";

    _bufferMutex->unlock();
    this_thread::sleep_for(milliseconds(33));
  }

  _processingActive = false;
}
