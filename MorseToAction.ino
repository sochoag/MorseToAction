#include "variables.h"
#include "btnToMorse.h"
#include "EMG.h"

void setup()
{
  Serial.begin(115200);
  initEMG();
  EMGCalibrate();
}

void loop()
{
  EMGValueDiscrete();
  bool result = false;
  for (byte it = 0; it < emgPinsSize; it++)
  {
    result = result || emgDiscrete[it];
  }
  readMorseInput(result);
  if (flag)
  {
    printf("Accion %d\n", action);
    flag = false;
  }
}