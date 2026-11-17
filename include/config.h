#pragma once

// Wiring (both modules on the default I2C bus)
//
//   Module         ESP32 (esp32dev)
//   ------------   ----------------
//   VCC      ->    3V3
//   GND      ->    GND
//   SCL      ->    GPIO22
//   SDA      ->    GPIO21
//
//   BMP390L: SDO -> GND, CSB high (I2C mode)
//   LSM6DS3: SDO pulled high on the module, CS high (I2C mode)
//
//   MicroSD breakout board+ (SPI)
//   5V       ->    5V (VIN)
//   GND      ->    GND
//   CLK      ->    GPIO18
//   DO       ->    GPIO19
//   DI       ->    GPIO23
//   CS       ->    GPIO5
//   Card must be formatted FAT16 or FAT32.

#define PIN_SDA 21
#define PIN_SCL 22

#define PIN_SD_SCK 18
#define PIN_SD_MISO 19  // DO
#define PIN_SD_MOSI 23  // DI
#define PIN_SD_CS 5

#define BMP390_ADDR 0x76   // SDO tied to GND
#define LSM6DS3_ADDR 0x6B  // SDO high

// Set this to your local sea-level pressure in hPa for an accurate altitude.
#define SEA_LEVEL_HPA 1013.25f

#define LOG_INTERVAL_MS 500  // 2 readings per second, to serial and SD
