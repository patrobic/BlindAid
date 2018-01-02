# Serial Port Emulation

## COM Port Assignment
The Bluetooth communication link simulated betweenthe virtual HC-05 bluetooth module attached to the Arduino Nano in Proteus, and the Serial class used by ControlRealtime in BlindAid, relies on virtual COM port pairing.

The COM ports are assigned as follows.
* COM1: HC-05 Bluetooth module -> Arduino Nano (Proteus Simulation)
* COM2: CSerial C++ Class -> ControlRealtime (BlindAid Project)

## Port Mapping Configuration
A shareware software (nags you to buy at startup, but can be bypassed for unlimited free usage) called Virtual Serial Port Emulator (VSPE, http://www.eterlogic.com/Products.VSPE.html) is used to virtually pair these two COM ports together.

The COM ports are mapped as follows.

* Click "Create New Device".
* Select Device Type "Pair".
* Select "Port 1" and "Port 2".
* Click "Start Emulation".

## Software Usage
By clicking the "Information" (I) button, a pane on the right opens, and by increasing the window size additional debug information can be seen.

* Connection details for both paired ports .
* Incoming and outgoing data statistics (byte count).
* Raw data transmission monitoring (text or binary).