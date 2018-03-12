# BlindAid
Capstone Project: Assist the blind in moving around safely by warning them of impending obstacles using depth sensing, computer vision, and tactile glove feedback.

## Launch Flags
### Default (to use menu)
	blindaid
	
### Production (autonomous mode)
	blindaid -a

### Production with debug enabled (to debug/demo)
	blindaid -d -a
	
### Production with glove disabled (to demo processing)
	blindaid -d -c

### Save test images
	blindaid -d -c -r 1000 (autosaves an image every second)
	blindaid -d -c -r (saves images on keypress)
	
### Load test images
	blindaid -d -c -t c:\record\YYYY-MM-DD_HH-MM-SS (show results on screen)
	blindaid -d -t c:\record\YYYY-MM-DD_HH-MM-SS (send results to glove)

### Help
	blindaid -?

## Operation Modes
The various modes in which the obstacle depth detection can be configured, and key parameters associated to each.

### Finger Regions
The default mode, partitions the depth frame into 5 vertical slices, centered in the frame, assigning each to the corresponding finger of the glove.
- RegionMode: Static
- Center: Middle
- HorizontalCoverage: 0.9
- VerticalCoverage: 0.9
- SnapToEdge: True
- RegionHeight: 0.4
- RegionWidth: 0.2

RegionSize Uniform                               RegionSize Varying
+---------------------------------------+        +---------------------------------------+
|                                       |        |                                       |
|    +-----+-----+-----+-----+-----+    |        |    +--------+---+---+---+--------+    |
|    |     |     |     |     |     |    |        |    |        |   |   |   |        |    |
|    |     |     |     |     |     |    |        |    |        |   |   |   |        |    |
|    +-----+-----+-----+-----+-----+    |        |    +--------+---+---+---+--------+    |
|    |     |     |     |     |     |    |        |    |        |   |   |   |        |    |
|    |     |     |  +  |     |     |    |        |    |        |   | + |   |        |    |
|    |     |     |     |     |     |    |        |    |        |   |   |   |        |    |
|    +-----+-----+-----+-----+-----+    |        |    +--------+---+---+---+--------+    |
|    |     |     |     |     |     |    |        |    |        |   |   |   |        |    |
|    |     |     |     |     |     |    |        |    |        |   |   |   |        |    |
|    +-----+-----+-----+-----+-----+    |        |    +--------+---+---+---+--------+    |
|                                       |        |                                       |
+---------------------------------------+        +---------------------------------------+

### Hand Hunting
Detects the position of the hand in the frame, and sets it as the center of the detection region, which is only a portion of the frame.
- RegionMode: Dynamic
- Center: N/A
- HorizontalCoverage: 0.5
- VerticalCoverage: 0.5
- SnapToEdge: True
- RegionHeight: 0.4
- RegionWidth: 0.2

SnapToEdge Disabled                            SnapToEdge Enabled
+---------------------------------------+      +--------------------+---+---+---+------+
|                                       |      |                    |   |   |   |      |
|                                       |      |                    |   |   |   |      |
|                                       |      |                    |   |   |   |      |
|                                       |      |                    |   |   |   |      |
|                 +--+---+---+---+--+   |      |                    |   |   |   |      |
|                 |  |   |   |   |  |   |      |                    |   |   |   |      |
|                 |  |   |   |   |  |   |      |                    |   |   |   |      |
|                 +--+---+---+---+--+   |      +--------------------+---+---+---+------+
|                 |  |   |   |   |  |   |      |                    |   |   |   |      |
|                 |  |   | + |   |  |   |      |                    |   | + |   |      |
|                 |  |   |   |   |  |   |      |                    |   |   |   |      |
|                 +--+---+---+---+--+   |      +--------------------+---+---+---+------+
|                 |  |   |   |   |  |   |      |                    |   |   |   |      |
+-----------------+--+---+---+---+--+---+      +--------------------+---+---+---+------+

### Head Protection
Sets the top middle as the center of the detection region, only detecting a narrow region where the user's head is likely to pass.
- RegionMode: Static
- Center: 320, 140
- HorizontalCoverage: 0.3
- VerticalCoverage: 0.7
- SnapToEdge: False
- RegionHeight: 0.4
- RegionWidth: 0.2

+----------+--+---+---+---+--+----------+
|          |  |   |   |   |  |          |
|          |  |   |   |   |  |          |
|          +--+---+---+---+--+          |
|          |  |   |   |   |  |          |
|          |  |   | + |   |  |          |
|          |  |   |   |   |  |          |
|          +--+---+---+---+--+          |
|          |  |   |   |   |  |          |
|          |  |   |   |   |  |          |
|          +--+---+---+---+--+          |
|                                       |
|                                       |
|                                       |
+---------------------------------------+

## Modules
The various modules supported which can be enabled or disabled, along with key parameters associated to each.

### DepthObstacle Detection
Uses the depth (IR Grayscale) image to detect the presence of nearby obstacles, warning the user of their position and distance via the glove's tactile feedback.
- 
- 
- 

### TrafficLight Detection
Uses the color (RGB) image to detect traffic lights in the upper portion of the frame, indicating to the user of their presence and color (red/yellow/green) via audible feedback.
- 
- 
- 
