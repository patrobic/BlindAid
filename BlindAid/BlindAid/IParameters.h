#pragma once

#define HORZ_REGIONS 3
#define VERT_REGIONS 5

// Interface for detection module parameters.
class IParameters
{
public:
  enum Toggle
  {
    Disabled,
    Enabled
  };

  Toggle GetToggle() { return _toggle; }

private:
  Toggle _toggle = Toggle::Enabled;

};