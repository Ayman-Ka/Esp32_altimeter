#include "Imu.h"

bool Imu::begin(uint8_t addr, TwoWire &wire) {
  if (!lsm_.begin_I2C(addr, &wire)) return false;

  lsm_.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
  lsm_.setGyroRange(LSM6DS_GYRO_RANGE_500_DPS);
  lsm_.setAccelDataRate(LSM6DS_RATE_104_HZ);
  lsm_.setGyroDataRate(LSM6DS_RATE_104_HZ);

  delay(100);  // gyro output is off right after power-on
  return true;
}

void Imu::read(ImuReading &out) {
  sensors_event_t accel, gyro, temp;
  lsm_.getEvent(&accel, &gyro, &temp);
  out.accel = {accel.acceleration.x, accel.acceleration.y, accel.acceleration.z};
  out.gyro = {gyro.gyro.x * SENSORS_RADS_TO_DPS,
              gyro.gyro.y * SENSORS_RADS_TO_DPS,
              gyro.gyro.z * SENSORS_RADS_TO_DPS};
}
