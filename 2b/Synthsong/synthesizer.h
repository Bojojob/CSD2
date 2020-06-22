#ifndef _SYNTHESIZER_H_
#define _SYNTHESIZER_H_
#include <iostream>
#include "sine.h"
#include "square.h"
#include "saw.h"

class Synthesizer {
public:
  Synthesizer();
  ~Synthesizer();

  Sine sine;
  Square square;
  Saw saw;

  void setSamplerate(float samplerate);
  void setFrequency(float frequency);
  void setAmplitude(float amplitude);

  float getSample();
  void tick();

protected:
  float amplitude;
  float frequency;
  float sample;
  float samplerate;

};
#endif
