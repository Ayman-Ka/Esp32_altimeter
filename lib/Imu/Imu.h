#pragma once

#include <Adafruit_LSM6DS3.h>

struct Vec3 {
  float x, y, z;
};

struct ImuReading {
  Vec3 accel;  // m/s^2, includes gravity
  Vec3 gyro;   // deg/s
};

// LSM6DS3 accelerometer + gyro.
class Imu {
 public:
  bool begin(uint8_t addr, TwoWire &wire);
  void read(ImuReading &out);

 private:
  Adafruit_LSM6DS3 lsm_;
};
