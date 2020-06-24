#include <iostream>
#include "fm_synthesizer.h"

fm_synthesizer::fm_synthesizer()  {
  amplitude = 1.0;
  sample = 0;
  fmAmount = 0;
  fmRatio = 0;

  Sine operator1;
  Sine operator2;
}

fm_synthesizer::~fm_synthesizer()  {

}

void fm_synthesizer::setSamplerate(float samplerate) {
  this->samplerate = samplerate;

  operator1.setSamplerate(samplerate);
  operator2.setSamplerate(samplerate);
}

void fm_synthesizer::setFrequency(float frequency) {
  this->frequency = frequency;

  setOp2Frequency();
}

void fm_synthesizer::setOp2Frequency()  {
  op2Frequency = frequency * fmRatio;
  operator2.setFrequency(op2Frequency);
}

void fm_synthesizer::setFmRatio(float fmRatio)  {
  this->fmRatio = fmRatio;
  setOp2Frequency();
}

void fm_synthesizer::setFmAmount(float fmAmount)  {
  this->fmAmount = fmAmount;
}

void fm_synthesizer::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float fm_synthesizer::getSample() {
  sample = operator1.getSample();
  return sample * amplitude;
}


void fm_synthesizer::updateFrequency()  {
  op1Frequency = frequency + (operator2.getSample() * fmAmount);
  operator1.setFrequency(op1Frequency);
}

void fm_synthesizer::tick()  {
  operator1.tick();
  operator2.tick();
}
