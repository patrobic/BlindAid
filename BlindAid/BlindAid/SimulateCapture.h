#pragma once

#include "IModule.h"
#include "ModuleCapture.h"

class CaptureSim : public IModule
{
public:
  void Init(std::string path, std::thread *thread, std::mutex *bufferMutex, bool *processingActive, cv::Mat *image);
  void Start();

private:
  void TCapture();

  std::string _path;
  std::thread *_thread;
  std::mutex *_bufferMutex;
  bool *_processingActive;
  cv::Mat *_image;

  cv::VideoCapture _cap;

};