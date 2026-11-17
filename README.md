# Sensor board

ESP32 reading a BMP390L (pressure/temperature) and an LSM6DS3 (accelerometer/gyro) over I2C twice per second, printing the values to the serial monitor and logging them to a microSD card.

## Hardware

| Module pin | ESP32   |
|------------|---------|
| VCC        | 3V3     |
| GND        | GND     |
| SCL        | GPIO22  |
| SDA        | GPIO21  |

- **BMP390L**: SDO to GND (address 0x76), CSB high
- **LSM6DS3**: SDO high (address 0x6B), CS high

MicroSD breakout board+ (SPI):

| Breakout pin | ESP32   |
|--------------|---------|
| 5V           | 5V (VIN) |
| GND          | GND     |
| CLK          | GPIO18  |
| DO           | GPIO19  |
| DI           | GPIO23  |
| CS           | GPIO5   |

The card must be formatted FAT16 or FAT32.

## Build and run

Open the project in VS Code with PlatformIO, then click **Upload and Monitor** (115200 baud).

## Output

```
T 23.37 C  P 992.52 hPa  Alt 174.0 m  |  Acc   0.04   0.32   9.97 m/s2  Gyro    -1.2    -0.6    -3.9 dps
```

| Field | Meaning |
|-------|---------|
| T     | Sensor temperature (°C) |
| P     | Air pressure (hPa) |
| Alt   | Altitude from pressure (m), relative to `SEA_LEVEL_HPA` |
| Acc   | Acceleration X/Y/Z (m/s²), includes gravity (~9.8 on the axis pointing up) |
| Gyro  | Rotation speed X/Y/Z (°/s), shows a small fixed offset when still |

## SD logging

Each boot creates a new file (`log_001.csv`, `log_002.csv`, ...) with one line per reading:

```
ms,temp_c,pressure_hpa,alt_m,ax,ay,az,gx,gy,gz
1234,23.37,992.52,174.0,0.04,0.32,9.97,-1.2,-0.6,-3.9
```

`ms` is the time since boot. Each line is saved immediately, so pulling the power loses at most the current line. A 512 MB card holds about 6 weeks of data.

## Project layout

```
include/config.h   pins, addresses, settings
lib/Barometer/     BMP390L driver
lib/Imu/           LSM6DS3 driver
lib/SdLogger/      CSV logging to SD card
src/main.cpp       setup and main loop
```

New modules go in their own folder under `lib/`.
# Esp32_altimeter
