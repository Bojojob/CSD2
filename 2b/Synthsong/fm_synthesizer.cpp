#include <iostream>
#include "fm_synthesizer.h"

Fm_synthesizer::Fm_synthesizer()  {
  amplitude = 1.0;
  sample = 0;
  fmAmount = 0;
  fmRatio = 0;

  Sine operator1;
  Sine operator2;
}

Fm_synthesizer::~Fm_synthesizer()  {

}

void Fm_synthesizer::setSamplerate(float samplerate) {
  this->samplerate = samplerate;

  operator1.setSamplerate(samplerate);
  operator2.setSamplerate(samplerate);
}

void Fm_synthesizer::setFrequency(float frequency) {
  this->frequency = frequency;

  setOp2Frequency();
}

void Fm_synthesizer::setOp2Frequency()  {
  op2Frequency = frequency * fmRatio;
  operator2.setFrequency(op2Frequency);
}

void Fm_synthesizer::setFmRatio(float fmRatio)  {
  this->fmRatio = fmRatio;

  setOp2Frequency();
}

void Fm_synthesizer::setFmAmount(float fmAmount)  {
  this->fmAmount = fmAmount;
}

void Fm_synthesizer::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float Fm_synthesizer::getSample() {
  sample = operator1.getSample();
  return sample * amplitude;
}

void Fm_synthesizer::updateFrequency()  {
  op1Frequency = frequency + (operator2.getSample() * fmAmount);
  operator1.setFrequency(op1Frequency);
}

void Fm_synthesizer::tick()  {
  operator1.tick();
  operator2.tick();
}
