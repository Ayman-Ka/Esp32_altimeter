#pragma once

// Project settings. Change a value here and re-upload; nothing else needs editing.
// The full wiring tables are in README.md (Hardware section).

// ---- I2C bus: BMP390L + LSM6DS3 ---------------------------------------------
// Both sensors share these two pins (the ESP32's default I2C pins).
#define PIN_SDA 21
#define PIN_SCL 22

// I2C addresses, set by each module's SDO pin.
#define BMP390_ADDR 0x76   // SDO to GND = 0x76, SDO to 3V3 = 0x77
#define LSM6DS3_ADDR 0x6B  // SDO high = 0x6B, SDO to GND = 0x6A

// ---- SPI bus: MicroSD breakout board+ ----------------------------------------
// The ESP32's default SPI pins. The card must be formatted FAT16 or FAT32.
#define PIN_SD_SCK 18   // breakout CLK
#define PIN_SD_MISO 19  // breakout DO
#define PIN_SD_MOSI 23  // breakout DI
#define PIN_SD_CS 5     // breakout CS

// ---- Measurement settings ----------------------------------------------------
// Sea-level pressure in hPa used to calculate altitude. 1013.25 is the standard
// value; for accurate altitude, set it to today's sea-level pressure from a
// local weather report.
#define SEA_LEVEL_HPA 1013.25f

// Time between readings in milliseconds. Each reading is printed to serial and
// written to the SD card. 500 = 2 readings per second.
#define LOG_INTERVAL_MS 500
