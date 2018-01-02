# Arduino Simulation Folder
Place any projects/data/schematics intended to design or test the Arduino circuit/communication here.

## Required Software Tools
Currently we are using the following software.
* CodeBlocks: arduino coding C++ development.
* Proteus: circuit simulation and virtual Bluetooth command testing.
* Virtual Serial Port Emulator: pair virtual COM ports for Bluetooth emulation.

## Configuration Steps
First the necessary software must be installed, then VSPE COM ports configured, and finally the BlindAid and Proteus projects opened and run.

### Software Installation
* Install CodeBlocks for Arduino from http://arduinodev.com/codeblocks/
* Install Proteus 8 Professional by following the directions in ProteusSimulation/README.md (https://wle.ir/hadi/4-Program/Proteus/P85SP0/P85SP0.rar)
* Install Virtual Serial Port Emulator from Arduino\VSPE\SetupVSPE.msi (http://www.eterlogic.com/Products.VSPE.html)
* Ensure that the latest version of BlindAid is cloned using SourceTree from https://github.com/patrobic/BlindAid

### Simulation Preparation
* Configure Virtual Serial Port Emulator by following the directions in Arduino\VSPE\README.md.
* Open, compile and run the BlindAid project. Hit "1" + "t" to run Realtime Control (simulating image load).
* Open the Proteus Project in Arduino\Proteus\BlindAidGlove.pdsprj, and press F12 to start simulation.

## Expected Results
If all is configured correctly, the following will be observed.
* BlindAid will load a sample image and repeatedly send a control command over COM2 (ex. Sent(23 bytes): <111222333444555aaabbb>).
* Proteus terminal window will show the command strings arriving, the oscilloscope will show PWM waveforms, and the motors will spin in proportion to the command values.

## Modifying Arduino Code
* Open the Codeblocks project from Arduino\CodeBlocks\BlindAidGlove\BlindAidGlove.cbp and make desired changes.
* Build the project by clicking the gear icon (Proteus is mapped to the build folder by relative path, simply relaunching the Proteus simulation will update it).