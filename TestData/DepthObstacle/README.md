# Depth Images
Properly encoded depth images saved from the R200 camera can not be observed from a typical image viewer program.

The image will appear mostly dark/black, because it cannot be properly mapped to a display.
This is NORMAL because the image contains a single 16 bit channel which represents the distance in millimeters (mm).
The range of a 16 bit image is 0-65536, whereas the typical depth is 500m to 5000m. Unrecognized areas contain value 0, and some unusual regions contain values upto 65536.

To view the images, the range of interest (i.e. 0-5000) of the 16 bit image must be scaled down and mapped to the 8 bit space (0-255) to provide a useful depth map.