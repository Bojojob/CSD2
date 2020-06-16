#ifndef _SYNTHESIZER_H_
#define _SYNTHESIZER_H_
#include <iostream>
#include "sine.h"
#include "square.h"
#include "saw.h"

class Synthesizer {
public:
  Synthesizer(float samplerate);
  ~Synthesizer();

  Sine sine;
  Square square;
  Saw saw;

  void setFrequency(float frequency);
  void setAmplitude(float amplitude);

  float getSample();

protected:
  float amplitude = 0.1;
  float frequency;
  float sample;
  float samplerate;

};
#endif
