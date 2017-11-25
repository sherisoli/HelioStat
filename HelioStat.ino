#include "PinDefinitions.h"
#include "Types.h"

#define BAUD_RATE 9600

/****************************************************************************************/

void setup() {
  Serial.begin(BAUD_RATE);
  initializeRTC();
  initializePins();
  initializeLocation();
  goToHomePositions();
}

void loop() {
  utcTime = getTimeFromRTClock();
  printUTCTime(utcTime);
}
