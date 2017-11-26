void homeAzimuth() {
  Serial.println("Moving to the Azimuth home Position: 90 degrees (East)");
  int stepCount;
  for (int stepCount = 0; stepCount < MAXAZHOMESTEP; stepCount++) {
    int optoStateAZ = digitalRead(OPTOPINAZ);
    if (optoStateAZ == LOW) { // optical sensor is not blocked
      digitalWrite(MOTAZCLK, HIGH);
      delay(STEPDLY);
      digitalWrite(MOTAZCLK, LOW);
      delay(STEPDLY);
    } else { // optical sensor is blocked
      // it has reached the azimuth home position
      break;
    }
  }
}

void homeZenith() {
  Serial.println("Moving to the Zenith home position: +90 degrees (Horizon)");
  int stepCount;
  for (int stepCount = 0; stepCount < MAXZEHOMESTEP; stepCount++) { // should be home in 180 deg worth of steps
    int optoStateZE = digitalRead(OPTOPINZE);
    if (optoStateZE == LOW) { // optical sensor is not blocked
      digitalWrite(MOTZECLK, HIGH);
      delay(STEPDLY);
      digitalWrite(MOTZECLK, LOW);
      delay(STEPDLY);
    } else { // optical sensor is blocked
      break;
    }
  }
}

void goToHomePositions() {
  Serial.println("Homing the tracker...");
  homeAzimuth();
  homeZenith();
  Serial.print("\n");
}

