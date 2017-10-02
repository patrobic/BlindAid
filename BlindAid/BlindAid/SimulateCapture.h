#pragma once

#include <atomic>

#include "IModule.h"
#include "ModuleCapture.h"

class CaptureSim : public IModule
{
public:
  void Init(bool isVideo, std::string path, std::thread *thread, std::mutex *bufferMutex, atomic_bool *captureDone, atomic_bool *newCapturedFrame, cv::Mat *image);
  void Start();

private:
  void TCaptureVideo();
  void TCapturePhoto();

  bool _isVideo;
  std::string _path;
  std::thread *_thread;
  std::mutex *_bufferMutex;
  atomic_bool *_captureDone;
  atomic_bool *_newCapturedFrame;

  cv::Mat *_image;

  cv::VideoCapture _cap;

};