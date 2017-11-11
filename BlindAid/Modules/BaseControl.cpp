#include "BaseControl.h"
#include "ModuleControl.h"
#include "SimulateControl.h"

ControlBase *ControlBase::MakeControl(IParameters *params, IData *input, IData *output)
{
  if (params->GetMode() == IParameters::Mode::Realtime)
    return new Control(params, input, output);
  else
    return new ControlSim(params, input, output);
}

ControlBase::ControlBase(IParameters *params, IData *input, IData *output)
{
  _params = static_cast<Parameters*>(params);
  _input = static_cast<Vision::Data*>(input);
  _output = static_cast<Data*>(output);
}

std::string ControlBase::CalculateVibrationValue(int pixel) // TODO: May belong instead in Control... not ControlBase?
{
  pixel = 255 - pixel; // TODO: implement function

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

  return std::string(3 - std::to_string(pixel).length(), '0') + std::to_string(pixel);
}

void ControlBase::CheckConsecutiveDetections() // TODO: probably does NOT belong here.
{
  // TODO: function that counts the number of consecutive detections of a given type (point & radius), and only accepts it once the count reaches a certain threshold.
  // Always store the detections of the previous image, along with an associated counter for each (starting at 1).
  // For each frame
  //    identify which current detections correspond to any last detections (threshold of distance and size scaling)
  //    if any do correspond
  //      overwrite previous detection with latest
  //      increment corresponding counter
  //    else
  //      delete the detection and counter
  //    for each counter-detection pair
  //       if the counter >= threshold
  //          act upon the detection (draw + feedback)

  // To do this, beef up the Results class of TrafficLight, so that each detection also includes a counter. (or should the results class be STUPID, and Control hold a copy of previous results and counter?)
  //    Where should the threshold checking be done? (TrafficLight, TrafficLight::Results, Control)???
}
