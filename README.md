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

Open the project in VS Code with PlatformIO, click the **→** (Upload) button in the status bar, then the **plug** icon to open the serial monitor (115200 baud).

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

## Setting up from scratch

1. **Install PlatformIO:** in VS Code open Extensions (Ctrl+Shift+X), search for **PlatformIO IDE**, click Install, then restart VS Code. The first start takes a few minutes while it downloads its tools.
2. **Install Git** from https://git-scm.com (default options are fine).
3. **Clone the repo** in a terminal:
   ```
   git clone https://github.com/Ayman-Ka/Esp32_altimeter.git
   ```
4. **Open the project:** in VS Code use File → Open Folder and pick the `Esp32_altimeter` folder (the one containing `platformio.ini`). PlatformIO downloads the ESP32 platform and the libraries automatically on the first build.
5. **Wire the hardware** as shown in the Hardware section above and plug the ESP32 in over USB.
6. **Upload:** click the **→** (Upload) button in the blue status bar at the bottom of VS Code.
7. **Open the serial monitor:** click the **plug** icon in the status bar to see the readings.

If the board isn't detected, install the CP210x USB driver from Silicon Labs. If an upload fails with "port is busy", close any other open serial monitor. If it hangs at "Connecting...", hold the board's **BOOT** button until uploading starts.
