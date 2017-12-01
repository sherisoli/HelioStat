/*
 * Moves the Azimuth motor the number of steps indicated.
 * steps: a positive number indicates clockwise motion,
 * while a negative number indicates counterclockwise motion.
 */
void MoveMotorAZ(int steps) {
  if (steps == 0) {
    return;
  } else if (steps > 0) {
    Serial.print("Moving Azimuth motor clockwise "); Serial.print(steps); Serial.print(" steps...\n");
    digitalWrite(MOTAZCWCCW, LOW); // positive # of steps means CW = LOW
  } else { // steps < 0
    steps = -steps; // absolute value
    Serial.print("Moving Azimuth motor counter-clockwise "); Serial.print(steps); Serial.print(" steps...\n");
    digitalWrite(MOTAZCWCCW, HIGH); // negative # of steps means CCW = HIGH
  }
  delay(10);
  for (int stepCount = 0; stepCount < steps; stepCount++) {
    digitalWrite(MOTAZCLK, HIGH);
    delay(STEPDLYAZ);
    digitalWrite(MOTAZCLK, LOW);
    delay(STEPDLYAZ);
  }
}

/*
 * Moves the Zenith motor the number of steps indicated.
 * steps: a positive number indicates clockwise motion,
 * while a negative number indicates counterclockwise motion.
 */
void MoveMotorZE(int steps) {
  if (steps == 0) {
    return;
  } else if (steps > 0) {
    Serial.print("Moving Zenith motor clockwise "); Serial.print(steps); Serial.print(" steps...\n");
    digitalWrite(MOTZECWCCW, LOW); // positive # of steps means CCW = LOW
  } else { // steps < 0
    steps = - steps; // absolute value
    Serial.print("Moving Zenith motor counter-clockwise "); Serial.print(steps); Serial.print(" steps...\n");
    digitalWrite(MOTZECWCCW, HIGH); // negative # of steps means CW = HIGH
  }
  delay(10);
  for (int stepCount = 0; stepCount < steps; stepCount++) {
    digitalWrite(MOTZECLK, LOW);
    delay(STEPDLYZE);
    digitalWrite(MOTZECLK, HIGH);
    delay(STEPDLYZE);
  }
}
