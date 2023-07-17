#ifndef variables_h
#define variables_h

const byte samples = 200;

static const byte emgPins[] = {33, 32, 35};
static const byte emgPinsSize = sizeof(emgPins);

int calibratedValue[emgPinsSize];
int maxVal[emgPinsSize];
bool emgDiscrete[emgPinsSize];

static const int calibrationTime = 5000;
static const int trashTime = 5000;

unsigned long setupTime;

#endif