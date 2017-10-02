#pragma once

#include <atomic>

#include "IModule.h"
#include "ModuleCapture.h"

class CaptureSim : public IModule
{
public:
  void Init(Data *data, std::thread *thread);
  void SetPath(bool isVideo, string colorPath, string depthPath);
  void Start();

private:
  void TCaptureVideo();
  void TCapturePhoto();

  string _colorPath;
  string _depthPath;
  bool _isVideo = false;

  Data *_data;
  std::thread *_thread;

  cv::VideoCapture _cap;
};