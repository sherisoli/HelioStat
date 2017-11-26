int iStepsAZ = STEPSAZHOME;
double dAngleZE = ANGLEZEHOME;
int iCurrentZEsteps = 8692;

void trackSolarVector(solarCoordinates utcSunCoordinates) {
  Serial.print("Tracking the solar vector...\n");
  int iDeltaStepsAZ, iDeltaStepsZE;
  iDeltaStepsAZ = (int)(utcSunCoordinates.degAzimuth * STEPSPERDEGAZ) - iStepsAZ;
  MoveMotorAZ(iDeltaStepsAZ);
  iStepsAZ = (int)(utcSunCoordinates.degAzimuth * STEPSPERDEGAZ);
  if (utcSunCoordinates.degZenith > 00.1 && utcSunCoordinates.degZenith < 89.9) {
    int iFutureZEsteps = getZenithSteps(utcSunCoordinates.degZenith);
    int deltaZenithSteps = iCurrentZEsteps - iFutureZEsteps; //store in getZenith result in variable
    MoveMotorZE(deltaZenithSteps);
    dAngleZE = utcSunCoordinates.degZenith;
    iCurrentZEsteps = iFutureZEsteps;
  } else {
    Serial.print("Returning to home position after dark...\n");
    homeAzimuth();
    homeZenith();
  }
  Serial.print("\n");
}

int getZenithSteps(double theta) {
  double beta0; // Initial guess
  double beta; // Approximate solution
  double epsilon; // Maximum error
  int maxIterations; // Maximum number of iterations
  int iterations; // Actual number of iterations
  int converged; // Whether iteration converged
  double thetaRAD = theta * rad;
  beta0 = 0;
  epsilon = 0.00001;
  maxIterations = 10000;
  double nutPosition = -1;
  // Find the first positive solution.
  while (nutPosition <= 0) {
    beta = newtonsMethod(beta0, epsilon, maxIterations, &iterations, &converged, thetaRAD);
    nutPosition = 25*cos(thetaRAD) + 53*cos(thetaRAD + PI + beta);
    beta0++;
  }
  return ((int)(nutPosition / 0.004));
}

double f(double thetaRAD, double beta) {
  return 15 + 25 * sin(thetaRAD) - 53 * sin(thetaRAD + beta);
}

double f_prime(double thetaRAD, double beta) {
  return -53 * cos(thetaRAD + beta); //the derivative
}

double newtonsMethod(double beta0, double epsilon, int maxIterations, int* iterations_p, int* converged_p, double thetaRAD ) {
  double beta = beta0;
  double beta_prev;
  int iter = 0;
  do {
    iter++;
    beta_prev = beta;
    beta = beta_prev - f(thetaRAD, beta_prev) / f_prime(thetaRAD, beta_prev);
  } while (fabs(beta - beta_prev) > epsilon && iter < maxIterations);
  if (fabs(beta - beta_prev) <= epsilon)
    *converged_p = 1;
  else
    *converged_p = 0;
  *iterations_p = iter;
  return beta;
}

test(getZenithSteps) {
  double argTheta = 45;
  int expectedZenithSteps = 4949;
  int actualZenithSteps = getZenithSteps(argTheta);
  assertNotEqual(expectedZenithSteps, actualZenithSteps);
}

test(f) {
  double thetaRAD = PI;
  double beta = PI/2;

  double expectedVal = 68.0;
  double actualVal = f(thetaRAD, beta);
  assertEqual(expectedVal, actualVal);
}

test(f_prime) {
  double thetaRAD = PI;
  double beta = PI/2;
  
  int expectedVal = 0;
  double actualVal = f_prime(thetaRAD, beta);
  assertEqual(expectedVal, (int)actualVal);
}
