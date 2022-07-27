#ifndef EMG_H
#define EMG_H

#include "buffer.h"
#include <EMGFilters.h>

static const byte emgPin = 27;
static const int calibrationTime = 10000;
static const int trashTime = 5000;

unsigned long setupTime;

float envlope = 0.0;

float maxValue = 0;
float minValue = 9999999999;
float bufferedValue = 0;

Buffer bufferEMG(2000);
EMGFilters myFilter;

void initEMG()
{
  bufferEMG.initBuffer();
  pinMode(emgPin,INPUT);
  myFilter.init(SAMPLE_FREQ_500HZ, NOTCH_FREQ_60HZ, true, true, true);
}

float emgRead()
{
  int value = analogRead(emgPin);
  int DataAfterFilter = myFilter.update(value);
  envlope = sq(DataAfterFilter);
  bufferEMG.addToBuffer(envlope);
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
    bufferedValue = emgRead();
  }
  Serial.println("Inicio calibración");
  while(now-setupTime<calibrationTime+trashTime)
  {
    now = millis();

    bufferedValue = emgRead();

    if(bufferedValue > maxValue)
    {
      maxValue = bufferedValue;
    }
    if(bufferedValue < minValue)
    {
      minValue = bufferedValue;
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