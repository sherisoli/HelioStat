#define MAXAZHOMESTEP 6250
#define MAXZEHOMESTEP 10000 // ZE home max subject to revision
#define STEPSAZHOME 1800 // AZ home position = East = +90 degrees = 1800 steps
#define ANGLEZEHOME 90.0 // ZE home position = Horizon = +90 degrees
#define STEPDLY 5

void homeAzimuth() {
  Serial.println("");
  Serial.println("Moving to the Azimuth Home Position: 90 degrees East");
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
  Serial.println("");
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
  homeAzimuth();
  homeZenith();
}

