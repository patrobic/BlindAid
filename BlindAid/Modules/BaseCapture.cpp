#include "BaseCapture.h"
#include "ModuleCapture.h"
#include "SimulateCapture.h"

CaptureBase *CaptureBase::MakeCapture(IParameters *params, IData *input, IData *output)
{
  if (params->GetMode() == IParameters::Mode::Realtime)
    return new Capture(params, input, output);
  else
    return new CaptureSim(params, input, output);
}

CaptureBase::CaptureBase(IParameters *params, IData *input, IData *output)
{
  _params = static_cast<Parameters*>(params);
  _input = input;
  _output = static_cast<Data*>(output);
}

void CaptureBase::CreateHsvImage()
{
  cvtColor(*_output->GetRgbImage(), *_output->GetHsvImage(), CV_BGR2HSV);
}
