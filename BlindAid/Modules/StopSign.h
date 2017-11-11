#pragma once

#include "DetectBase.h"
#include "CaptureBase.h"

namespace Vision
{
  namespace StopSign
  {
    struct Parameters : public IParameters
    {
    public:
      bool Valid()
      {
        return true;
      }

    private:
    };

    class Data : public IData
    {
    public:
      void Clear() { _circle.Clear(); }
      bool Valid()
      {
        return true;
      }

      Circle GetRegion() { return _circle; }
      void SetRegion(Circle circle) { _circle = circle; }

    private:
      Circle _circle;
    };

    class Detect : public DetectBase<Parameters, Capture::Data, Data>
    {
    public:
      Detect(IParameters *params, IData *input, IData *output);

    private:
      void Process();
      void PreProcess();
    };
  }
}