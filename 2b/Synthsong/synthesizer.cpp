#include <iostream>
#include "synthesizer.h"

Synthesizer::Synthesizer()  {
  amplitude = 1.0;
  sample = 0;

  Sine sine;
  Square square;
  Saw saw;
}

Synthesizer::~Synthesizer()  {

}

void Synthesizer::setSamplerate(float samplerate) {
  this->samplerate = samplerate;

  sine.setSamplerate(samplerate);
  square.setSamplerate(samplerate);
  saw.setSamplerate(samplerate);
}

void Synthesizer::setFrequency(float frequency) {
  this->frequency = frequency;

  sine.setFrequency(frequency);
  square.setFrequency(frequency);
  saw.setFrequency(frequency);
}

void Synthesizer::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float Synthesizer::getSample() {
  sample = (sine.getSample() + square.getSample() + saw.getSample());
  sample /= 3;
  return sample;
}

void Synthesizer::tick()  {
  sine.tick();
  square.tick();
  saw.tick();
}
