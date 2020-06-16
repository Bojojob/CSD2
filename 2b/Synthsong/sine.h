#ifndef _SINE_H_
#define _SINE_H_
#include "oscillator.h"

class Sine : public Oscillator {
public:
  Sine();
  ~Sine();

  float tick(double samplerate);

};
#endif
