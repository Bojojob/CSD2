#ifndef _FM_SYNTHESIZER_H_
#define _FM_SYNTHESIZER_H_
#include "sine.h"

//a simple two operator fm synth

class Fm_synthesizer {
public:
  Fm_synthesizer();
  ~Fm_synthesizer();

  Sine operator1;
  Sine operator2;

  void setSamplerate(float samplerate);
  void setOp2Frequency();
  void setFrequency(float frequency);
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
