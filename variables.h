#ifndef variables_h
#define variables_h

int samples = 200;

static const byte emgPins[] = {33, 32};
static const byte emgPinsSize = sizeof(emgPins);

float calibratedValue[emgPinsSize];
float currentValue[emgPinsSize];
float maxVal[emgPinsSize];
bool emgDiscrete[emgPinsSize];

static const int calibrationTime = 5000;
static const int trashTime = 5000;

unsigned long setupTime;

#endif