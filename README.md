# ArduinoRTCawake
This small project shows a sketch where we are using Arduino's LowPower library in SLEEP_FOREVER mode being awakened every minute by an RTC.

This project was tested using Arduino Mega 2560 and RTC module 3231 wich has 6 connections (GND, VCC, SDA, SCL, SQW and 32K).

The libraries used are Wire.h which is necessary to communicate to RTC module (by i2c), RTClibExtended.h which provides many functions for the RTC module and LowPower.h for sleep mode.

In this project Arduino is just blinking a LED 2 times and then go to sleep. It will be awake every minute.
In the tests with a power supply giving 12.35V the consumption in the sleep mode went to 30mA (considering that Arduino is also supplying RTC module). When awake the consumption goes to normal level.
