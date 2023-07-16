#ifndef EMG_H
#define EMG_H

#include <EMGFilters.h>

EMGFilters emgFilters[emgPinsSize];

void initEMG()
{
  for (int it = 0; it < emgPinsSize; it++)
  {
    pinMode(emgPins[it], INPUT);
    emgFilters[it].init(SAMPLE_FREQ_1000HZ, NOTCH_FREQ_60HZ, true, true, true);
  }
}

void emgRead()
{
  for (int it = 0; it < emgPinsSize; it++)
  {
    maxVal[it] = 0.0;
  }
  for (int count = 0; count <= samples; count++)
  {
    int value[emgPinsSize];
    int DataAfterFilter[emgPinsSize];
    float envelope[emgPinsSize];
    for (int it = 0; it < emgPinsSize; it++)
    {
      value[it] = analogRead(emgPins[it]);
      DataAfterFilter[it] = emgFilters[it].update(value[it]);
      envelope[it] = sq(DataAfterFilter[it]);
      if (envelope[it] > maxVal[it])
      {
        maxVal[it] = envelope[it];
      }
    }
  }
}

void EMGCalibrate()
{
  setupTime = millis();
  printf("Trash\n");
  while (millis() - setupTime < trashTime)
  {
    emgRead();
  }
  printf("Calibration\n");
  setupTime = millis();
  while (millis() - setupTime < calibrationTime)
  {
    emgRead();
    for (int it = 0; it < emgPinsSize; it++)
    {
      calibratedValue[it] = calibratedValue[it] > maxVal[it] ? calibratedValue[it] : maxVal[it];
    }
  }
}

void EMGValueDiscrete()
{
  emgRead();
  for (int it = 0; it < emgPinsSize; it++)
  {
    emgDiscrete[it] = maxVal[it] > calibratedValue[it] ? true : false;
  }
}

#endif