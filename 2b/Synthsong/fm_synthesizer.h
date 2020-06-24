#ifndef _fm_synthesizer_H_
#define _fm_synthesizer_H_
#include <iostream>
#include "sine.h"

class fm_synthesizer {
public:
  fm_synthesizer();
  ~fm_synthesizer();

  Sine operator1;
  Sine operator2;

  void setSamplerate(float samplerate);
  void setFrequency(float frequency);
  void setOp2Frequency();
  void setFmRatio(float fmRatio);
  void setFmAmount(float fmAmount);
  void setAmplitude(float amplitude);

  float getSample();

  void updateFrequency();
  void tick();

protected:
  float amplitude;
  float frequency;
  float op1Frequency;
  float op2Frequency;
  float fmAmount;
  float fmRatio;
  float sample;
  float samplerate;

};
#endif
