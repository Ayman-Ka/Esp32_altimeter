#pragma once

#include <Adafruit_BMP3XX.h>

struct BaroReading {
  float tempC;
  float pressureHpa;
  float altitudeM;
};

// BMP390L pressure/temperature sensor.
class Barometer {
 public:
  bool begin(uint8_t addr, TwoWire &wire, float seaLevelHpa);
  bool read(BaroReading &out);

 private:
  Adafruit_BMP3XX bmp_;
  float seaLevelHpa_ = 1013.25f;
};
