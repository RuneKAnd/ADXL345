ADXL345
=======

This code for Arduino collects raw accelerometer data and calculates roll and pitch


USAGE
-----

  GetRawData will allow you to read the data coming in directly from the accelerometer axis and calibrate the readings. Place the sensor on a flat surface and determine which axis is measuring gravity, adjust the corresponding XYZcorrection values to zero the other 2 axis. Rotate the sensor so that a different axis is measuring gravity and adjust the last value of XYZcorrection.
