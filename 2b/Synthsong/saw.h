#ifndef _SAW_H_
#define _SAW_H_
#include "oscillator.h"

class Saw : public Oscillator {
public:
  Saw();
  ~Saw();

  float tick(double samplerate);

};
#endif
