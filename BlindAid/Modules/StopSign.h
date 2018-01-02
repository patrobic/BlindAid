#pragma once

#include "IDetect.h"
#include "Capture.h"

namespace Vision
{
  namespace StopSign
  {
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

    class Detect : public IDetect<Parameters, Capture::Data, Data>
    {
    public:
      Detect(IParameters *params, IData *input, IData *output);

    private:
      void Process();
    };
  }
}