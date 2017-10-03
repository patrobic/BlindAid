#include "SimulateCapture.h"

using namespace std;
using namespace std::chrono;
using namespace cv;

void CaptureSim::Init(Data *data)
{
  _data = data;
}

void CaptureSim::operator()()
{
  _data->_captureDone = false;

  if (_data->_params.GetMediaType())
  {
    _cap.open(_data->_params.GetColorSimDataPath());
    _data->_captureThread = thread(&CaptureSim::VideoCaptureThread, this);
  }
  else
  {
    _data->_captureThread = thread(&CaptureSim::PhotoCaptureThread, this);
  }
}

void CaptureSim::VideoCaptureThread()
{
  int frame = 0;
  _data->_depthImage = imread(_data->_params.GetDepthSimDataPath());

  do 
  {
    frame++;

    steady_clock::time_point start = steady_clock::now();
    _data->_bufferMutex.lock();
    _data->_captureDone = !_cap.read(_data->_colorImage);
    _data->_bufferMutex.unlock();
    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);

    _data->_newFrameForVision = true;

    cout << "[CAPTURE] Frame " << to_string(frame) << " load time : " << time_span.count() * 1000 << "ms.\n";
    this_thread::sleep_for(milliseconds(33));
  }
  while (!_data->_captureDone);

  _data->_captureDone = true;
}

void CaptureSim::PhotoCaptureThread()
{
  _data->_bufferMutex.lock();

  _data->_colorImage = imread(_data->_params.GetColorSimDataPath());
  _data->_depthImage = imread(_data->_params.GetDepthSimDataPath());
  if (_data->_colorImage.cols == 0 || _data->_colorImage.rows == 0) throw("could not open image.");

  _data->_bufferMutex.unlock();
  _data->_newFrameForVision = true;

  cout << "[CAPTURE] Photo loaded.\n";
  _data->_captureDone = true;
}