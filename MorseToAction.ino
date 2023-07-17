#include "variables.h"
#include "btnToMorse.h"
#include "espNowMaster.h"

// Modo 1 Visualizacion de señales emg
// Modo 2 EMG y ESPNOW
// Modo 3 Bluetooth y ESPNOW

// #define monitor
// #define emg
#define bluetooth

#ifdef monitor
#include "EMG.h"
#endif

#ifdef emg
#include "EMG.h"
#endif

#ifdef bluetooth
#include "espBT.h"
#endif

void setup()
{
  Serial.begin(115200);
  setupEspNow();
#if defined(monitor) || defined(emg)
  initEMG();
  EMGCalibrate();
#elif defined(bluetooth)
  setupBT();
#endif
}

void loop()
{
#if defined(monitor) || defined(emg)
  EMGValueDiscrete();
#endif
#if defined(monitor)
  for (byte it = 0; it < emgPinsSize; it++)
  {
    printf("Calibrated%d:%d\n", it, calibratedValue[it]);
    printf("Sensor%d:%d\n", it, maxVal[it]);
  }
#elif defined(emg)
  bool result = false;
  for (byte it = 0; it < emgPinsSize; it++)
  {
    result = result || emgDiscrete[it];
  }
  readMorseInput(result);
  if (flag)
  {
    Send.accion = action;
    sendEspNow();
    flag = false;
  }
#elif defined(bluetooth)
  checkBT();
  if (flag)
  {
    Send.accion = action;
    sendEspNow();
    flag = false;
  }
#endif
}