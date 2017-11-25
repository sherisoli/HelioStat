//Latitude and Longitude for McMaster (JHE) = 43.260181 (N), 79.920892 (W). Latitude is considered positive to the North and longitude to the East.
//Use decimal format (Latitude = 43 + 26.0181/60 = 43.434; Longitude = -1 * (79 degrees + 92.0892/60) = -80.535;)
const double MCMASTERLATITUDE = 43.434;
const double MCMASTERLONGITUDE = -80.535;

void initializeLocation() {
  utcLocation.dLatitude = MCMASTERLATITUDE;
  utcLocation.dLongitude = MCMASTERLONGITUDE;
  Serial.println("Location: McMaster University, Hamilton, ON");
  Serial.print("Latitude (Decimal Format): ");
  Serial.println(utcLocation.dLatitude);
  Serial.print("Longitude (Decimal Format): ");
  Serial.println(utcLocation.dLongitude);
  Serial.println("");
}

