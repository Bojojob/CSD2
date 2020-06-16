#include "saw.h"
#include "math.h"

Saw::Saw() : Oscillator() {
}

Saw::~Saw() {
}

// saw wave formula
float Saw::tick(double samplerate) {
  phase += frequency / samplerate;
  sample = ((fmod(phase,1)*2)-1)*amplitude;

  return getSample();
  
}