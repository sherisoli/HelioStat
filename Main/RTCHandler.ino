#include <Wire.h>
#include "RTClib.h"
#include <TimeLib.h>
#define HOURSTOUTC 5
#define SECPERHOUR 3600
#define SECPERDAY 86400
#define DEMOTIMEFACTOR 120 // factory by which to accelerate time

DS1307 rtc;
DateTime startTime;

void initializeRTC() {
  Wire.begin(); // join I2C bus
  rtc.begin();
  startTime = DateTime(__DATE__, __TIME__);
  rtc.adjust(startTime); // sketch compilation local time
}

/*
 * Returns the current UTC time as a calendar struct.
 * See Types.h for a definition of this data type.
 */
calendar getTimeFromRTClock() {
  struct calendar currentTime;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  if (Wire.requestFrom(DS1307_ADDRESS, 7) == 7) { // request 7 bytes from DS1307
    currentTime.seconds = bcdToDec(Wire.read());
    currentTime.minutes = bcdToDec(Wire.read());
    currentTime.hours = bcdToDec(Wire.read()) + HOURSTOUTC;
    if (currentTime.hours >= 24) {
      currentTime.hours = 0;
    }

    Wire.read(); // day of the week
    currentTime.day = bcdToDec(Wire.read());
    currentTime.month = bcdToDec(Wire.read());
    currentTime.year = bcdToDec(Wire.read()) + 2000;

    return currentTime;
  } else {
    Serial.println(F("Failed to get RTC date and time"));
  };
}

byte bcdToDec(byte bcdVal) {
  return ((bcdVal / 16 * 10) + (bcdVal % 16));
}

void printUTCTime(calendar utcTime) {
  Serial.println("Universal Time Coordinates - UTC");
  Serial.print("Date (DD/MM/YY): ");
  printTimeNum(utcTime.day);
  Serial.print("/");
  printTimeNum(utcTime.month);
  Serial.print("/");
  printTimeNum(utcTime.year);

  Serial.println("");
  Serial.print("Time (HH/MM/SS): ");
  printTimeDouble(utcTime.hours);
  Serial.print(":");
  printTimeDouble(utcTime.minutes);
  Serial.print(":");
  printTimeDouble(utcTime.seconds);
  Serial.print("\n");
  Serial.print("\n");
}

void printTimeNum(int num) {
  if (num < 10) {
    Serial.print("0");
  }
  Serial.print(num, DEC); // decimal notation
}

void printTimeDouble(double val) {
  if ((int)val < 10) {
    Serial.print("0");
  }
  Serial.print((int)val);
}

/* For demo purposes only.
 * Condenses 24 hours into 12 minutes.
 * Therefore, 1 minute represents
 * 2 elapsed hours.
 */
calendar getAcceleratedTime() {
    struct calendar acceleratedTime;
    struct calendar currentUTCTime = getTimeFromRTClock();

    DateTime currentTime = DateTime(currentUTCTime.year, currentUTCTime.month, currentUTCTime.day, (int)currentUTCTime.hours, (int)currentUTCTime.minutes, (int)currentUTCTime.seconds);

    long startTimeUnix = startTime.unixtime() + HOURSTOUTC*SECPERHOUR;
    long currentTimeUnix = currentTime.unixtime();

    long elapsedSecondsUnix;
    if (currentTimeUnix >= startTimeUnix) {
      elapsedSecondsUnix = currentTimeUnix - startTimeUnix;
    } else {
      elapsedSecondsUnix = (SECPERDAY - startTimeUnix) + currentTimeUnix;
    }

    unsigned long acceleratedTotalSeconds = elapsedSecondsUnix*DEMOTIMEFACTOR + startTimeUnix;
    time_t raw_time = acceleratedTotalSeconds;

    acceleratedTime.seconds = second(raw_time);
    acceleratedTime.minutes = minute(raw_time);
    acceleratedTime.hours = hour(raw_time);
    acceleratedTime.day = day(raw_time);
    acceleratedTime.month = month(raw_time);
    acceleratedTime.year = year(raw_time);

    return acceleratedTime;
}
