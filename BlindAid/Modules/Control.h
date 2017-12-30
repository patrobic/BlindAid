#pragma once

#include "IModule.h"
#include "Vision.h"
#include "ControlParameters.h"

namespace Control
{
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

    float _vibrationIntensity[VERT_REGIONS + 2];
  };
}