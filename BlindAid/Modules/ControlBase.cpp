#include "ControlBase.h"
#include "ControlRealtime.h"
#include "ControlSimulate.h"

namespace Control
{
  Base *Base::MakeControl(IParameters *params, IData *input, IData *output)
  {
    if (((Control::Parameters*)params)->GetMode() == SwitchableParameters::Mode::Realtime)
      return new Realtime::Realtime(params, input, output);
    else
      return new Simulate::Simulate(params, input, output);
  }

  Base::Base(IParameters *params, IData *input, IData *output) : IModule(params, input, output)
  {

  }

  void Base::MapVibrationValues()
  {
    _output->Clear();

    for (int i = 0; i < VERT_REGIONS; ++i)
      for (int j = 0; j < HORZ_REGIONS; ++j)
      {
        float distanceMeters = PixelToMeters(_input->GetDepthObstacleResults()->GetRegionIntensity(i, j)); // convert given region pixel distance to meters.

        _vibrationIntensity[i] = max(_vibrationIntensity[i], MappingFunction(distanceMeters, i, j)); // map the value to a vibration intensity ratio, and the maximum for that finger.
      }
  }

  float Base::MappingFunction(float distance, int col, int row)
  {
    if (distance < _params->GetNearestBound() || distance > _params->GetFarthestBound(col, row))
      return 0.f;

    else
    {
      float slope = (_params->GetMaximumVibration() - _params->GetMinimumVibration()) / (_params->GetFarthestBound(col, row) - _params->GetNearestBound());

      return (distance - _params->GetNearestBound()) * slope + _params->GetMinimumVibration();
    }

    // TODO: design algorithm that calculates vibrator control value (voltage/factor/whatever is required by the API controlling the Arduino/glove).
    // Should implement a function that maps the nearest pixel intensity value to control value in some non-linear way,
    // giving higher weight to near objects (possibly negative exponential function?).
    // [intensity]
    // |.......
    // |       .....
    // |            ...
    // |               ..
    // |                 .
    // |__________________._____________ [distance]
    // 0             128             255
  }

  float Base::PixelToMeters(int pixel)
  {
    // TODO: more complex mapping once we test camera, if conversion is non-linear.
    return pixel / 255.f * _params->GetMaximumDepthSpec();;
  }

  int Base::MetersToPixel(float meters)
  {
    return (int)(meters / _params->GetMaximumDepthSpec() * 255);
  }
}