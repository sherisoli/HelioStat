#include <Wire.h>
#include "RTClib.h"

DS1307 rtc;

#define BAUD_RATE 9600
#define DS1307_ADDRESS 0x68

struct calendar {
  int year;
  int month;
  int day;
  double hours;
  double minutes;
  double seconds;
};

struct calendar utcTime;

/****************************************************************************************/

void getTimeFromRTClock() {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  if (Wire.requestFrom(DS1307_ADDRESS, 7) == 7) { // request 7 bytes from DS1307
    utcTime.seconds = bcdToDec(Wire.read()); //& 0x7F
    utcTime.minutes = bcdToDec(Wire.read());
    utcTime.hours = bcdToDec(Wire.read()); //& 0x3f

    Wire.read(); // day of week
    utcTime.day = bcdToDec(Wire.read());
    utcTime.month = bcdToDec(Wire.read());
    utcTime.year = bcdToDec(Wire.read()) + 2000;

    printUTCTime();
  } else{
    Serial.println(F("Failed to get RTC date and time")); 
  };
}

byte bcdToDec(byte bcdVal) {
  return ((bcdVal/16 * 10) + (bcdVal%16));
}

void printUTCTime() {
    Serial.println("");
    Serial.println("Universal Time Coordinate - UTC");
    Serial.println("Date [DD/MM/YY]: ");
    printTimeNum(utcTime.day);
    Serial.print("/");
    printTimeNum(utcTime.month);
    Serial.print("/");
    printTimeNum(utcTime.year);

    Serial.println("");
    Serial.println("Time [HH/MM/SS]: ");
    printTimeDouble(utcTime.hours);
    Serial.print(":");
    printTimeDouble(utcTime.minutes);
    Serial.print(":");
    printTimeDouble(utcTime.seconds);
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

/****************************************************************************************/

void setup() {
  Serial.begin(BAUD_RATE);
  Wire.begin(); // join I2C bus
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  getTimeFromRTClock();
}
