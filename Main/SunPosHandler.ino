// Solar Vector computation derived from the journal paper
// "Computing the Solar Vector" Solar Energy 70(5), 431-441, 2001
// authors M. Blanco-Muriel, D.C. Alarcon-Padilla, T. Lopez-Moratalla, and M. Lara-Coira

/*
 * Returns the solar vector coordinates given the current UTC
 * time and the current location. See Types.h for a definition
 * of the data types.
 */
solarCoordinates getSunPos(struct calendar utcTime, struct location utcLocation) {
  Serial.print("Finding the sun's position...\n");
  struct solarCoordinates utcSunCoordinates;
  
  double dElapsedJulianDays;
  double dDecimalHours;
  double dEclipticLongitude;
  double dEclipticObliquity;
  double dRightAscension;
  double dDeclination;
  double dY;
  double dX;
  // Calculate difference in days between the current Julian Day
  // and JD 2451545.0, which is noon 1 January 2000 Universal Time
  {
    double dJulianDate;
    long int liAux1;
    long int liAux2;
    // Calculate time of the day in UT decimal hours
    dDecimalHours = utcTime.hours + (utcTime.minutes
                                      + utcTime.seconds / 60.0 ) / 60.0;
    // Calculate current Julian Day
    liAux1 = (utcTime.month - 14) / 12;
    liAux2 = (1461 * (utcTime.year + 4800 + liAux1)) / 4 + (367 * (utcTime.month
             - 2 - 12 * liAux1)) / 12 - (3 * ((utcTime.year + 4900
                                         + liAux1) / 100)) / 4 + utcTime.day - 32075;
    dJulianDate = (double)(liAux2) - 0.5 + dDecimalHours / 24.0;
    // Calculate difference between current Julian Day and JD 2451545.0
    dElapsedJulianDays = dJulianDate - 2451545.0;
  }
  // Calculate ecliptic coordinates (ecliptic longitude and obliquity of the
  // ecliptic in radians but without limiting the angle to be less than 2*Pi
  // (i.e., the result may be greater than 2*Pi)
  {
    double dMeanLongitude;
    double dMeanAnomaly;
    double dOmega;
    dOmega = 2.1429 - 0.0010394594 * dElapsedJulianDays;
    dMeanLongitude = 4.8950630 + 0.017202791698 * dElapsedJulianDays; // Radians
    dMeanAnomaly = 6.2400600 + 0.0172019699 * dElapsedJulianDays;
    dEclipticLongitude = dMeanLongitude + 0.03341607 * sin( dMeanAnomaly )
                         + 0.00034894 * sin( 2 * dMeanAnomaly ) - 0.0001134
                         - 0.0000203 * sin(dOmega);
    dEclipticObliquity = 0.4090928 - 6.2140e-9 * dElapsedJulianDays
                         + 0.0000396 * cos(dOmega);
  }
  // Calculate celestial coordinates ( right ascension and declination ) in radians
  // but without limiting the angle to be less than 2*Pi (i.e., the result may be
  // greater than 2*Pi)
  {
    double dSin_EclipticLongitude;
    dSin_EclipticLongitude = sin( dEclipticLongitude );
    dY = cos( dEclipticObliquity ) * dSin_EclipticLongitude;
    dX = cos( dEclipticLongitude );
    dRightAscension = atan2( dY, dX );
    if ( dRightAscension < 0.0 ) dRightAscension = dRightAscension + twoPI;
    dDeclination = asin( sin( dEclipticObliquity ) * dSin_EclipticLongitude );
  }
  // Calculate local coordinates ( azimuth and zenith angle ) in degrees
  {
    double dGreenwichMeanSiderealTime;
    double dLocalMeanSiderealTime;
    double degLatitudeInRadians;
    double dHourAngle;
    double dCos_Latitude;
    double dSin_Latitude;
    double dCos_HourAngle;
    double dParallax;
    dGreenwichMeanSiderealTime = 6.6974243242 +
                                 0.0657098283 * dElapsedJulianDays
                                 + dDecimalHours;
    dLocalMeanSiderealTime = (dGreenwichMeanSiderealTime * 15
                              + utcLocation.degLongitude) * rad;
    dHourAngle = dLocalMeanSiderealTime - dRightAscension;
    degLatitudeInRadians = utcLocation.degLatitude * rad;
    dCos_Latitude = cos( degLatitudeInRadians );
    dSin_Latitude = sin( degLatitudeInRadians );
    dCos_HourAngle = cos( dHourAngle );
    utcSunCoordinates.degZenith = (acos( dCos_Latitude * dCos_HourAngle
                                       * cos(dDeclination) + sin( dDeclination ) * dSin_Latitude));
    dY = -sin( dHourAngle );
    dX = tan( dDeclination ) * dCos_Latitude - dSin_Latitude * dCos_HourAngle;
    utcSunCoordinates.degAzimuth = atan2( dY, dX );
    if ( utcSunCoordinates.degAzimuth < 0.0 )
      utcSunCoordinates.degAzimuth = utcSunCoordinates.degAzimuth + twoPI;
    utcSunCoordinates.degAzimuth = utcSunCoordinates.degAzimuth / rad;
    // Parallax Correction
    dParallax = (dEarthRadius / dAstroUnit)
                * sin(utcSunCoordinates.degZenith);
    utcSunCoordinates.degZenith = (utcSunCoordinates.degZenith
                                       + dParallax) / rad;
  }
  Serial.print("Zenith angle (deg): ");
  Serial.println(utcSunCoordinates.degZenith);
  Serial.print("Azimuth angle (deg): ");
  Serial.println(utcSunCoordinates.degAzimuth);
  Serial.print("\n");
  return utcSunCoordinates;
}

test(getSunPos) {
  struct calendar currentTime;
  currentTime.seconds = 55;
  currentTime.minutes = 21;
  currentTime.hours = 17;
  currentTime.month = 11;
  currentTime.day = 26;
  currentTime.year = 2017;

  struct location currentLocation; // McMaster Location
  currentLocation.degLatitude = 43.434;
  currentLocation.degLongitude = -80.535;

  struct solarCoordinates expectedSunCoordinates;
  expectedSunCoordinates.degZenith = 64.57;
  expectedSunCoordinates.degAzimuth = 183.19;
  
  struct solarCoordinates actualSunCoordinates = getSunPos(currentTime, currentLocation);

  assertEqual((int)expectedSunCoordinates.degZenith, (int)actualSunCoordinates.degZenith);
  assertEqual((int)expectedSunCoordinates.degAzimuth, (int)actualSunCoordinates.degAzimuth);
}
