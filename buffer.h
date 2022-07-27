#ifndef BUFFER_H
#define BUFFER_H

#include "Arduino.h"

class Buffer
{
  private:
    float sum;
    int index;
    float *buf;
  public:
    byte size;
    Buffer(byte size);
    void initBuffer();
    void addToBuffer(float value);
    float getMeanValue();
};
#endif