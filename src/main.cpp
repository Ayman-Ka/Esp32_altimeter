// BMP390L (pressure/temperature) + LSM6DS3 (accel/gyro), printed to serial and
// logged to SD card. Wiring is in README.md, settings in include/config.h.

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Barometer.h>
#include <Imu.h>
#include <SdLogger.h>
#include "config.h"

Barometer baro;
Imu imu;
SdLogger logger;
bool baroOk = false;
bool imuOk = false;
bool sdOk = false;

unsigned long lastLog = 0;

void setup() {
  Serial.begin(115200);
  delay(300);
  Wire.begin(PIN_SDA, PIN_SCL);
  SPI.begin(PIN_SD_SCK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);

  baroOk = baro.begin(BMP390_ADDR, Wire, SEA_LEVEL_HPA);
  Serial.println(baroOk ? "BMP390L ready" : "BMP390L not found - check wiring");

  imuOk = imu.begin(LSM6DS3_ADDR, Wire);
  Serial.println(imuOk ? "LSM6DS3 ready" : "LSM6DS3 not found - check wiring");

  if (!baroOk && !imuOk) {
    Serial.println("No sensors available, halting");
    while (true) delay(1000);
  }

  sdOk = logger.begin(PIN_SD_CS, "ms,temp_c,pressure_hpa,alt_m,ax,ay,az,gx,gy,gz");
  if (sdOk) {
    Serial.printf("Logging to %s\n", logger.fileName());
  } else {
    Serial.println("SD card not found - check wiring and FAT format, not logging");
  }
}

void loop() {
  unsigned long now = millis();
  if (now - lastLog < LOG_INTERVAL_MS) return;
  lastLog = now;

  BaroReading b;
  bool haveBaro = baroOk && baro.read(b);
  ImuReading m;
  if (imuOk) imu.read(m);

  // Serial: readable line
  if (haveBaro) {
    Serial.printf("T %.2f C  P %.2f hPa  Alt %.1f m", b.tempC, b.pressureHpa, b.altitudeM);
  } else if (baroOk) {
    Serial.print("BMP390L read failed");
  }
  if (imuOk) {
    if (baroOk) Serial.print("  |  ");
    Serial.printf("Acc %6.2f %6.2f %6.2f m/s2  Gyro %7.1f %7.1f %7.1f dps",
                  m.accel.x, m.accel.y, m.accel.z, m.gyro.x, m.gyro.y, m.gyro.z);
  }
  Serial.println();

  // SD: CSV line, missing values left empty
  if (sdOk) {
    char baroCsv[40] = ",,";
    char imuCsv[64] = ",,,,,";
    if (haveBaro) {
      snprintf(baroCsv, sizeof(baroCsv), "%.2f,%.2f,%.1f", b.tempC, b.pressureHpa, b.altitudeM);
    }
    if (imuOk) {
      snprintf(imuCsv, sizeof(imuCsv), "%.2f,%.2f,%.2f,%.1f,%.1f,%.1f",
               m.accel.x, m.accel.y, m.accel.z, m.gyro.x, m.gyro.y, m.gyro.z);
    }
    char line[128];
    snprintf(line, sizeof(line), "%lu,%s,%s", now, baroCsv, imuCsv);
    logger.writeLine(line);
  }
}
