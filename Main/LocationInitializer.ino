/* 
 *  Latitude and Longitude coordinates for the John Hodgins Engineering Building
 *  in McMaster University, Hamilton, ON, Canada
*/
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

