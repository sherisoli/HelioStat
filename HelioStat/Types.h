struct calendar {
  int year;
  int month;
  int day;
  double hours;
  double minutes;
  double seconds;
};

struct cLocation {
  double dLongitude;
  double dLatitude;
};

struct cSunCoordinates {
  double dZenithAngle;
  double dAzimuth;
};

struct calendar utcTime;
struct cLocation utcLocation;
struct cSunCoordinates utcSunCoordinates;
