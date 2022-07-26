#ifndef FINGER_H
#define FINGER_H

#include <ESP32Servo.h>

static const byte numFingers = 6;
//static const byte fingersPins[numFingers]={2,32,33,25,14,15};
static const byte fingersPins[numFingers]={2,14,33,32,25,15};
// Motor A
int motor1Pin1 = 18;
int motor1Pin2 = 19;

Servo finger[numFingers];

void initFingers()
{
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  for(byte i=0;i<numFingers;i++)
  {
    finger[i].setPeriodHertz(100);
    finger[i].attach(fingersPins[i],1000,2000);
  } 
}

void pos_normal() 
{
  Serial.println("pos_normal");
  finger[1].write(1300);
  finger[2].write(1300);
  finger[3].write(1300);
  finger[4].write(1300);
  finger[0].write(1300);////pulgar
  delay(500);
}

void tecleo() 
{
  Serial.println("tecleo");
  finger[1].write(1800);///meñique
  finger[2].write(1800);////medio
  finger[3].write(1300);////indice
  finger[4].write(1800);////anular
  finger[0].write(1800);////pulgar
  delay(500);
}

void agarre_cilindrico() 
{
  Serial.println("agarre_cilindrico");
  finger[1].write(1800);
  finger[2].write(1800);
  finger[3].write(1800);
  finger[4].write(1800);
  delay(500);
}

void agarre_punta() 
{
  Serial.println("agarre_punta");
  finger[3].write(130);
  finger[4].write(25);
  finger[2].write(25);
  finger[1].write(25);
  finger[0].write(25);
  delay(500);
}
void agarre_lateral() 
{
  Serial.println("agarre_lateral");
  finger[3].write(130);
  finger[4].write(25);
  finger[2].write(25);
  finger[1].write(25);
  finger[0].write(25);
  delay(500);
}
void agarre_cilindricosmall() 
{
  Serial.println("agarre_cilindricosmall");
  finger[0].write(115);
  finger[1].write(115);
  finger[2].write(125);
  finger[3].write(130);
  finger[4].write(130);
  delay(500);
}
void agarre_gancho() 
{
  Serial.println("agarre_gancho");
  finger[4].write(95);
  finger[3].write(100);
  finger[2].write(100);
  finger[1].write(100);
  finger[0].write(100);
  delay(500);
}
void flexion() 
{
  Serial.println("flexion");
  finger[5].write(-30);
  delay(1000);
}

void extension() {
  Serial.println("extension");
  finger[5].write(80);
  delay(1000);
}

#endif