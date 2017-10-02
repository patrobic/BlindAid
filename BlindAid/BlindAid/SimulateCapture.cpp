#include "SimulateCapture.h"

void CaptureSim::Init(Data *data, std::thread *thread)
{
  _data = data;
  _thread = thread;
}

void CaptureSim::SetPath(bool isVideo, string colorPath, string depthPath)
{
  _colorPath = colorPath;
  _depthPath = depthPath;
  _isVideo = isVideo;
}

void CaptureSim::Start()
{
  _data->_captureDone = false;

  if (_isVideo)
  {
    _cap.open(_colorPath);
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
  _data->_depthImage = imread(_depthPath);

  do 
  {
    frame++;

    time_point<steady_clock> start = steady_clock::now();
    _data->_bufferMutex.lock();
    _data->_captureDone = !_cap.read(_data->_colorImage);
    _data->_bufferMutex.unlock();
    time_point<steady_clock> end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    _data->_newCapturedFrame = true;

    cout << "[CAPTURE] Frame " << to_string(frame) << " load time : " << time_span.count() * 1000 << "ms.\n";
    this_thread::sleep_for(milliseconds(33));
  }
  while (!_data->_captureDone);

  _data->_captureDone = true;
}

void CaptureSim::TCapturePhoto()
{
  _data->_bufferMutex.lock();

  _data->_colorImage = imread(_colorPath);
  _data->_depthImage = imread(_depthPath);
  if (_data->_colorImage.cols == 0 || _data->_colorImage.rows == 0) throw("could not open image.");

  _data->_bufferMutex.unlock();
  _data->_newCapturedFrame = true;

  cout << "[CAPTURE] Photo loaded.\n";
  _data->_captureDone = true;
}