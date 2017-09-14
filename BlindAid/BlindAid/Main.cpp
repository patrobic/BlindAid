#include "Main.h"
#include <iostream>

using namespace std;

void main()
{
  Main main;
  main.Start();
}

void Main::Start()
{
  cout << "=== Main Menu ===\n1: Settings\n2: Calibrate\n3: Start Detection\n";

  system("pause");
  return;
}
