#pragma once

#define HORZ_REGIONS 3
#define VERT_REGIONS 5

class GlobalParameters;

enum Toggle { Disabled, Enabled };
enum Mode { Realtime, Simulate };

// Interface for detection module parameters.
class IParameters
{
public:
  IParameters(GlobalParameters *params)
  {
    _globalParameters = params;
  }

  virtual bool Valid() = 0;
  virtual void Defaults() = 0;

  bool GetToggle() { return true; }

  GlobalParameters *GetGlobalParameters() { return _globalParameters; }

protected:
  GlobalParameters *_globalParameters;
};

class SwitchableParameters : public IParameters
{
public:
  SwitchableParameters(GlobalParameters *params) : IParameters(params)
  {

  }

  // TODO: check that data is valid when received by a module.
  virtual bool Valid() = 0;

  Toggle GetToggle() { return _toggle; }
  void SetToggle(Toggle toggle) { _toggle = toggle; }

  Mode GetMode() { return _mode; }
  void SetMode(Mode mode) { _mode = mode; }

protected:
  // allows toggling a module between enabled and disabled.
  Toggle _toggle = Toggle::Enabled;

  // allows switching a module from realtime to simulation modes.
  Mode _mode = Mode::Realtime;
};