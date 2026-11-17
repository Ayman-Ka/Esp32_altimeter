#include "SdLogger.h"

bool SdLogger::begin(uint8_t csPin, const char *header) {
  if (!SD.begin(csPin)) return false;

  // First unused name; after 999 files the last one gets overwritten.
  for (int i = 1; i <= 999; i++) {
    snprintf(fileName_, sizeof(fileName_), "/log_%03d.csv", i);
    if (!SD.exists(fileName_)) break;
  }

  file_ = SD.open(fileName_, FILE_WRITE);
  if (!file_) return false;
  file_.println(header);
  file_.flush();
  return true;
}

void SdLogger::writeLine(const char *line) {
  if (!file_) return;
  file_.println(line);
  file_.flush();  // so nothing is lost if power is cut
}
