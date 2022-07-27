#include "btnToMorse.h"
#include "finger.h"
#include "EMG.h"

void setup() {
  Serial.begin(115200);
  initButton();
  initFingers();
  initEMG();
  EMGCalibrate();
}

void loop() 
{
  bool input = digitalRead(34) || EMGValueDiscrete();
  readMorseInput(input);           // read the button state  
  if(flag)
  {
    flag = false;
    Serial.println(action);
    switch (action)
    {
      case 0: pos_normal(); break;
      case 1: tecleo(); break;
      case 2: agarre_cilindrico(); break;
      case 3: agarre_punta(); break;
      case 4: agarre_lateral(); break;
      case 5: agarre_cilindricosmall(); break;
      case 6: agarre_gancho(); break;
      case 7: flexion(); break;
      case 8: extension(); break;
    }
  }
}