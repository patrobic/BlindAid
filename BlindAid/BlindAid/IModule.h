#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\features2d.hpp"

using namespace std;
using namespace std::chrono;

class IModule
{
public:
  //virtual void Init() = 0;
  virtual void Start() = 0;

private:

};