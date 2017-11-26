//Latitude and Longitude for McMaster (JHE) = 43.260181 (N), 79.920892 (W). Latitude is considered positive to the North and longitude to the East.
//Use decimal format (Latitude = 43 + 26.0181/60 = 43.434; Longitude = -1 * (79 degrees + 92.0892/60) = -80.535;)
#define MCMASTERLATITUDE 43.434;
#define MCMASTERLONGITUDE -80.535;

void initializeLocation() {
  currentLocation.degLatitude = MCMASTERLATITUDE;
  currentLocation.degLongitude = MCMASTERLONGITUDE;
  Serial.print("Initializing location...\n");
  Serial.print("Location: McMaster University, Hamilton, ON\n");
  Serial.print("Latitude (deg): ");
  Serial.println(currentLocation.degLatitude);
  Serial.print("Longitude (Decimal Format): ");
  Serial.println(currentLocation.degLongitude);
  Serial.print("\n");
}

