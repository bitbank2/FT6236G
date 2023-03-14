FT6236G capacitive touch sensor library<br>
---------------------------------------
Copyright (c) 2023 BitBank Software, Inc.<br>
Written by Larry Bank<br>
bitbank@pobox.com<br>
<br>
FocalTech makes many different capacitive touch controllers and this library supports the FT6x36 ones in a generic way. Each has different capabilities and usually come pre-programmed for the specific pixel width and height of the target application. A feature supported by this library that may not be present in the device you're using is the touch area and pressure values. Some of their controllers also have built-in gesture detection. The common features of the FT6x36 controllers is that they will generate an interrupt signal when a touch event is occurring. There's no configuration options for this feature; it's always enabled. This library allows you to request the latest touch information and it returns the number of active touch points (0-2) along with the coordinates (and pressure/area of each if available).
