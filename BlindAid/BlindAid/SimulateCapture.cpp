#include "SimulateCapture.h"

void CaptureSim::Init(bool isVideo, std::string path, std::thread *thread, std::mutex *bufferMutex, atomic_bool *captureDone, atomic_bool *newCapturedFrame, cv::Mat *image)
{
  _isVideo = isVideo;
  _path = path;
  _thread = thread;
  _captureDone = captureDone;
  _newCapturedFrame = newCapturedFrame;
  _bufferMutex = bufferMutex;
  _image = image;
}

void CaptureSim::Start()
{
  *_captureDone = false;

  if (_isVideo)
  {
    _cap.open(_path);
    *_thread = thread(&CaptureSim::TCaptureVideo, this);
  }
  else
  {
    *_thread = thread(&CaptureSim::TCapturePhoto, this);
  }
}

void CaptureSim::TCaptureVideo()
{
  int frame = 0;

  do 
  {
    frame++;

    time_point<steady_clock> start = steady_clock::now();
    _bufferMutex->lock();
    *_captureDone = !_cap.read(*_image);
    _bufferMutex->unlock();
    time_point<steady_clock> end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    *_newCapturedFrame = true;

    cout << "[CAPTURE] Frame " << to_string(frame) << " load time : " << time_span.count() * 1000 << "ms.\n";
    this_thread::sleep_for(milliseconds(33));
  }
  while (!*_captureDone);

  *_captureDone = true;
}

void CaptureSim::TCapturePhoto()
{
  _bufferMutex->lock();

  *_image = cv::imread(_path);
  if (_image->cols == 0 || _image->rows == 0) throw("could not open image.");

  _bufferMutex->unlock();
  *_newCapturedFrame = true;

  cout << "[CAPTURE] Photo loaded.\n";
  *_captureDone = true;
}