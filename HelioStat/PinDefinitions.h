#define OPTOPINAZ 2 // optical sensor pin for Azimuth tracking stage
#define OPTOPINZE 3 // optical sensor pin for Zenith tracking stage
#define MOTAZCWCCW 7 // Azimuth CW/CCW motor driver pin
#define MOTAZCLK 6 // Azimuth motor CLK pin
#define MOTZECWCCW 5 // Zenith CW/CCW motor driver pin
#define MOTZECLK 4 // Zenith motor CLK pin
#define DS1307_ADDRESS 0x68 // address of DS1307 RT Clock

void initializePins() {
  pinMode(MOTAZCWCCW, OUTPUT);
  pinMode(MOTAZCLK, OUTPUT);
  pinMode(OPTOPINAZ, INPUT);
  pinMode(MOTZECWCCW, OUTPUT);
  pinMode(MOTZECLK, OUTPUT);
  pinMode(OPTOPINZE, INPUT);
}

