#include "buffer.h"

Buffer::Buffer(byte size)
{
  this->sum = 0;
  this->index = 0;
  this->size = size;
  this->buf = (float *)malloc(this->size * sizeof(float));
}

void Buffer::initBuffer()
{
  for(int i=0; i<this->size;i++)
  {
    this->buf[i] = 0;
  }
}

void Buffer::addToBuffer(float value)
{
  this->sum -= this->buf[this->index];
  this->sum += value;
  this->buf[this->index] = value;
  this->index = (this->index + 1) % this->size; 
}

float Buffer::getMeanValue()
{
  return this->sum/this->size;
}