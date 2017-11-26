#include <Wire.h>
#include "RTClib.h"

DS1307 rtc;

void initializeRTC() {
  Wire.begin(); // join I2C bus
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

calendar getTimeFromRTClock() {
  struct calendar currentTime;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  if (Wire.requestFrom(DS1307_ADDRESS, 7) == 7) { // request 7 bytes from DS1307
    currentTime.seconds = bcdToDec(Wire.read());
    currentTime.minutes = bcdToDec(Wire.read());
    currentTime.hours = bcdToDec(Wire.read());

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
