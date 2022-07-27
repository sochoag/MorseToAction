#ifndef EMG_H
#define EMG_H

#include "buffer.h"
#include <EMGFilters.h>

static const byte emgPin = 15;
static const int calibrationTime = 10000;
static const int trashTime = 5000;

unsigned long setupTime;

float envlope = 0.0;
float alpha = 0.05;
float S = envlope;

float minValue = 99999;
float maxValue = 0;
bool calibrated = false;

Buffer bufferEMG(1500);
EMGFilters myFilter;

void initEMG()
{
  bufferEMG.initBuffer();
  myFilter.init(SAMPLE_FREQ_500HZ, NOTCH_FREQ_60HZ, true, true, true);
}

float emgRead()
{
  int value = analogRead(emgPin);
  int DataAfterFilter = myFilter.update(value);

  envlope = sq(DataAfterFilter);

  S = (alpha * abs(DataAfterFilter)) + ((1 - alpha) * S);
  bufferEMG.addToBuffer(S);

  return bufferEMG.getMeanValue();
}

void EMGCalibrate()
{
  unsigned long now = millis();
  setupTime = millis();
  Serial.println("Inicio trash");
  while(now-setupTime < trashTime)
  {
    now = millis();
    emgRead();
  }
  Serial.println("Inicio calibración");
  while(now-setupTime<calibrationTime+trashTime)
  {
    now = millis();

    float bufferedValue = emgRead();

    if(bufferedValue < minValue)
    {
      minValue = bufferedValue;
    }
    if(bufferedValue > maxValue)
    {
      maxValue = bufferedValue;
    }
  }
  Serial.println("Fin calibración");
}

bool EMGValueDiscrete()
{
  float emgValue = emgRead(); 

  return map(emgValue, minValue, maxValue, 0, 1);
}

#endif