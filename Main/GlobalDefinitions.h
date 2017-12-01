// pin definitions
#define OPTOPINAZ 2 // optical sensor pin for Azimuth tracking stage
#define OPTOPINZE 3 // optical sensor pin for Zenith tracking stage
#define MOTAZCWCCW 7 // Azimuth CW/CCW motor driver pin
#define MOTAZCLK 6 // Azimuth motor CLK pin
#define MOTZECWCCW 5 // Zenith CW/CCW motor driver pin
#define MOTZECLK 4 // Zenith motor CLK pin

#define DS1307_ADDRESS 0x68 // address of DS1307 RT Clock

// arithmetic definitions
#define pi 3.1415926535897932384
#define twoPI (2.0*pi)
#define rad (pi/180.0)
#define dEarthRadius 6371.01 // km
#define dAstroUnit 149597890 // km

// motor definitions
#define STEPSPERDEGAZ 20.0 // 1.8 deg per step and 36:1 reduction worm gears
#define STEPDLYZE 2
#define STEPDLYAZ 1

// home position definitions
#define MAXAZHOMESTEP 6250
#define MAXZEHOMESTEP 10000 // ZE home max subject to revision
#define STEPSAZHOME 1800 // AZ home position = East = +90 degrees = 1800 steps
#define ANGLEZEHOME 90.0 // ZE home position = Horizon = +90 degrees

#define BAUD_RATE 9600
struct location currentLocation;

void initializePins() {
  pinMode(MOTAZCWCCW, OUTPUT);
  pinMode(MOTAZCLK, OUTPUT);
  pinMode(OPTOPINAZ, INPUT);
  pinMode(MOTZECWCCW, OUTPUT);
  pinMode(MOTZECLK, OUTPUT);
  pinMode(OPTOPINZE, INPUT);
}

