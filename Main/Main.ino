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
  // demo(); // uncomment to run app in an accelerated time space (24 hours = 12 minutes)

  struct calendar currentTime = getTimeFromRTClock();
  printUTCTime(currentTime);
  struct solarCoordinates currentSunPos = getSunPos(currentTime, currentLocation);
  trackSolarVector(currentSunPos);
}

// Demo: condenses 24 hours into 12 minutes for demo purposes only
void demo() {
  struct calendar demoTime = getAcceleratedTime();
  printUTCTime(demoTime);
  struct solarCoordinates currentSunPos = getSunPos(demoTime, currentLocation);
  trackSolarVector(currentSunPos);
}

