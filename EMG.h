#ifndef EMG_H
#define EMG_H
void initEMG()
{
  for (int it = 0; it < emgPinsSize; it++)
  {
    pinMode(emgPins[it], INPUT);
  }
}

void emgRead()
{
  for (int it = 0; it < emgPinsSize; it++)
  {
    maxVal[it] = 0;
  }
  for (int count = 0; count <= samples; count++)
  {
    int value[emgPinsSize];
    for (int it = 0; it < emgPinsSize; it++)
    {
      value[it] = analogRead(emgPins[it]);
      if (value[it] > maxVal[it])
      {
        maxVal[it] = value[it];
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