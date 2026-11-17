#pragma once

#include <SD.h>

// Writes CSV lines to a new file on the SD card each boot (/log_001.csv, /log_002.csv, ...).
class SdLogger {
 public:
  // Call SPI.begin() first. Writes `header` as the file's first line.
  bool begin(uint8_t csPin, const char *header);
  void writeLine(const char *line);
  const char *fileName() const { return fileName_; }

 private:
  File file_;
  char fileName_[16] = "";
};
