#include "Types.h"
#include "GlobalDefinitions.h"
#include <ArduinoUnit.h>

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("SOLAR TRACKER");
  initializeRTC();
  initializePins();
  initializeLocation();
  goToHomePositions();
}

void loop() {
  // Test::run(); // uncomment to run ArduinoUnit unit tests
  struct calendar currentTime = getTimeFromRTClock();
  printUTCTime(currentTime);
  struct solarCoordinates currentSunPos = getSunPos(currentTime, currentLocation);
  trackSolarVector(currentSunPos);
}
