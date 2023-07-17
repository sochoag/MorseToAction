#ifndef ESPBT_H
#define ESPBT_H

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setupBT()
{
  SerialBT.begin("MAKI DERECHA");
}

void checkBT()
{
  if (SerialBT.available())
  {
    char val = SerialBT.read();
    switch (val)
    {
    case 'a':
      Serial.println("Llego la \"a\"");
      action = 1;
      flag = true;
      break;
    case 'b':
      Serial.println("Llego la \"b\"");
      action = 2;
      flag = true;
      break;
    case 'c':
      Serial.println("Llego la \"c\"");
      action = 3;
      flag = true;
      break;
    case 'd':
      Serial.println("Llego la \"d\"");
      action = 4;
      flag = true;
      break;
    case 'e':
      Serial.println("Llego la \"e\"");
      action = 5;
      flag = true;
      break;
    case 'f':
      Serial.println("Llego la \"f\"");
      action = 6;
      flag = true;
      break;
    case 'g':
      Serial.println("Llego la \"g\"");
      action = 7;
      flag = true;
      break;
    case 'h':
      Serial.println("Llego la \"h\"");
      action = 8;
      flag = true;
      break;
    case 'i':
      Serial.println("Llego la \"i\"");
      action = 9;
      flag = true;
      break;
    case 'j':
      Serial.println("Llego la \"j\"");
      action = 10;
      flag = true;
      break;
    case 'k':
      Serial.println("Llego la \"k\"");
      action = 11;
      flag = true;
      break;
    case 'l':
      Serial.println("Llego la \"l\"");
      action = 12;
      flag = true;
      break;
    case 'm':
      Serial.println("Llego la \"m\"");
      action = 13;
      flag = true;
      break;
    case 'n':
      Serial.println("Llego la \"n\"");
      action = 14;
      flag = true;
      break;
    }
  }
}

#endif
