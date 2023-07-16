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
  emgRead();
  for (int it = 0; it < emgPinsSize; it++)
  {
    printf("Sensor%d:%f\n", it, maxVal[it]);
    printf("CalibratedValue%d:%f\n", it, calibratedValue[it]);
  }
  // printf("Max:%f\n", maxVal);
  // delay(100);
  // bool input = EMGValueDiscrete();
  // readMorseInput(input); // read the button state
  // if (flag)
  // {
  //   flag = false;
  //   Serial.println(action);
  // }
}