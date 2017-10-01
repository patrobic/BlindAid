#pragma once

#define COL_REGIONS 5
#define ROW_REGIONS 3

class Settings
{
public:
  void LoadFile();

  int _numberOfVerticalSlices;
  int _numberOfHorizontalSections;

private:
};