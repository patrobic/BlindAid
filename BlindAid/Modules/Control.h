#pragma once

#include "IModule.h"
#include "Vision.h"
#include "ControlParameters.h"

namespace Control
{
  class Result
  {
  public:
    Result(int size)
    {
      _vibration.resize(size);
    }

    void Update(float intensity)
    {
      _vibration[index++%_vibration.size()] = intensity;
    }

    float Get()
    {
      float intensity = (float)INT_MAX;

      for (int i = 0; i < _vibration.size(); ++i)
        intensity = std::min(intensity, _vibration[i]);

      return intensity;
    }

  private:
    int index = 0;

    std::vector<float> _vibration;
  };

  class Data : public IData
  {
  public:
    bool Valid()
    {
      return true;
    }

    void Clear() { }

  private:

  };

  class Base : public IModule<Parameters, Vision::Data, Data>
  {
  public:
    Base(IParameters *params, IData *input, IData *output);
    static Base * MakeControl(IParameters * params, IData * input, IData * output);

  protected:
    void MapVibrationValues();
    float MappingFunction(float distance, int col, int row);

    Result *_vibrationIntensity[VERT_REGIONS + 2];
  };
}