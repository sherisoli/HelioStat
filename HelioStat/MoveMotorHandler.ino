void MoveMotorAZ(int steps) {
  Serial.print("Moving Azimuth motor this many steps: ");
  Serial.println(steps);
  if (steps == 0) {
    return;
  } else if (steps > 0) {
    digitalWrite(MOTAZCWCCW, LOW); // positive # of steps means CW = LOW
  } else { // steps < 0
    steps = -steps; // absolute value
    digitalWrite(MOTAZCWCCW, HIGH); // negative # of steps means CCW = HIGH
  }
  delay(10);
  for (int stepCount = 0; stepCount < steps; stepCount++) {
    digitalWrite(MOTAZCLK, HIGH);
    delay(STEPDLY);
    digitalWrite(MOTAZCLK, LOW);
    delay(STEPDLY);
  }
}

void MoveMotorZE(int steps) {
  Serial.print("Moving Zenith motor this many steps: ");
  Serial.println(steps);
  if (steps == 0) {
    return;
  } else if (steps > 0) {
    digitalWrite(MOTZECWCCW, HIGH); // positive # of steps means CW = LOW
  } else { // steps < 0
    steps = - steps; // absolute value
    digitalWrite(MOTZECWCCW, LOW); // negative # of steps means CCW = HIGH
  }
  delay(10);
  for (int stepCount = 0; stepCount < steps; stepCount++) {
    digitalWrite(MOTAZCLK, HIGH);
    delay(STEPDLY);
    digitalWrite(MOTZECLK, LOW);
    delay(STEPDLY);
  }
}
