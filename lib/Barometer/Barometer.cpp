#include "Barometer.h"

bool Barometer::begin(uint8_t addr, TwoWire &wire, float seaLevelHpa) {
  seaLevelHpa_ = seaLevelHpa;
  if (!bmp_.begin_I2C(addr, &wire)) return false;

  bmp_.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp_.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp_.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp_.setOutputDataRate(BMP3_ODR_50_HZ);

  // performReading() starts a conversion but returns the previous one's result,
  // so the first call returns garbage. Make it here and let the conversion finish.
  bmp_.performReading();
  delay(50);
  return true;
}

bool Barometer::read(BaroReading &out) {
  if (!bmp_.performReading()) return false;
  out.tempC = bmp_.temperature;
  out.pressureHpa = bmp_.pressure / 100.0f;
  // Same formula as the library's readAltitude(), which would trigger a second reading.
  out.altitudeM = 44330.0f * (1.0f - powf(out.pressureHpa / seaLevelHpa_, 0.1903f));
  return true;
}
