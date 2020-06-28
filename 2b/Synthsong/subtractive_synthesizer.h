#ifndef _SUBTRACTIVE_SYNTHESIZER_H_
#define _SUBTRACTIVE_SYNTHESIZER_H_
#include "sine.h"
#include "square.h"
#include "saw.h"

class Subtractive_synthesizer {
public:
  Subtractive_synthesizer();
  ~Subtractive_synthesizer();

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
