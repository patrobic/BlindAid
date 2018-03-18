# BlindAid
Capstone Project: Assist the blind in moving around safely by warning them of impending obstacles using depth sensing, computer vision, and tactile glove feedback.

## CONFIGURATION MODES: BlindAid can be launched and configured in 3 ways.
    Arguments: Launch from command line, configured with no interaction by passing arguments.
    User Menu: Launch without arguments, configured through a user interactive menu interface.
    Shortcuts: To simplify mode selection, create desktop shortcuts with argument combinations.

## USAGE: Summary of flags by category.
    COMMAND     [FLAGS]                                                 (CATEGORY)
    blindaid    [-a | -c | -t <path> | -s <path> -r [delay] [path]]     (operation mode selection)
                [-d -v [level] -l]                                      (debugging performance options)
                [-p <port> -cc <count>]                                 (miscellaneous settings)
                [-do {fr | hp} -tl {dl | bd}]                           (processing module selection)
                [-coloroff | -depthoff]                                 (image channel selection)

## DETAILS: Description of flags and parameters.
    -FLAG [ARGUMENT]    DESCRIPTION             (DETAILS)                                       [CHANGES]
    -a                  Realtime Mode           (bypass menu, no user interaction)              [Camera ON /Glove ON]
    -c                  Camera Only             (disable glove, print control to screen)        [Camera ON / Glove OFF]
    -t <path>           Glove Only              (disable camera, load images from disk)         [Camera OFF/Glove ON]
    -s <path>           Simulate Mode           (disable performance optimizations)             [Camera OFF/Glove OFF]
    -r [delay] [path]   Record Enabled          (save images to disk, 0 for manual)             [Record ON]
    -d                  Display Images          (show color/depth images to screen)             [Display ON]
    -v [level]          Verbose Messages        (print info messages to screen)                 [Logging ON]
    -l                  Low Performance         (disable multi threading optimizations)         [Threads OFF]
    -p <port #>         Set COM Port Number     (for Bluetooth glove connection)
    -cc [count]         Set Consecutive Count   (number of detections before warning)
    -do {fr | hp}       Depth Obstacle Mode     (fixed regions/hand position)                   [DepthObstacle FR/HP]
    -tl {dl | bd}       Traffic Light Mode      (deep learning/blob detector)                   [TrafficLight DL/BD]
    -coloroff           Depth Image Only        (disable color stream processing)               [Color OFF]
    -depthoff           Color Image Only        (disable depth stream processing)               [Depth OFF]
    -?                  Show Help               (show flag descriptions)

## SCENARIOS: Useful argument combinations.
    COMMAND  FLAGS              DESCRIPTION             (PURPOSE)
    blindaid                    Menu Interface          (manual configuration, via interactive menu)
    blindaid -a                 Realtime Final          (complete experience, for final product demo)
    blindaid -c                 Capture Only            (to demo without glove, print control to screen)
    blindaid -t path            Control Only            (to demo without camera, load images from disk)
    blindaid -s path            Simulate All            (disable camera and glove, only test software loop)
    blindaid -r ms              Record Images           (save images periodically, or 0 for manual trigger)
    blindaid -a -d              Realtime w\Debug        (full experience w\image display, low performance)
    blindaid -c -d              Capture w\Debug         (capture only w\display, to demonstrate processing)
	
## Shortcut Icons
	1) the FULL experience, NO display (for final demo).
	2) disable glove, NO display (mainly for benchmarking).
	3) FULL experience, WITH images on screen (to give in depth look into program).
	4) disable glove, WITH images on screen (so we don't have to worry about the glove's battery/connection).
	
## Modules
The various modules supported which can be enabled or disabled, along with key parameters associated to each.

### DepthObstacle Detection
Uses the depth (IR Grayscale) image to detect the presence of nearby obstacles, warning the user of their position and distance via the glove's tactile feedback.

### TrafficLight Detection
Uses the color (RGB) image to detect traffic lights in the upper portion of the frame, indicating to the user of their presence and color (red/yellow/green) via audible feedback.