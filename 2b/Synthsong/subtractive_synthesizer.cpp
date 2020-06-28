#include <iostream>
#include "subtractive_synthesizer.h"

Subtractive_synthesizer::Subtractive_synthesizer()  {
  amplitude = 1.0;
  sample = 0;

  Sine sine;
  Square square;
  Saw saw;
}

Subtractive_synthesizer::~Subtractive_synthesizer()  {

}

void Subtractive_synthesizer::setSamplerate(float samplerate) {
  this->samplerate = samplerate;

  sine.setSamplerate(samplerate);
  square.setSamplerate(samplerate);
  saw.setSamplerate(samplerate);
}

void Subtractive_synthesizer::setFrequency(float frequency) {
  this->frequency = frequency;

  sine.setFrequency(frequency);
  square.setFrequency(frequency);
  saw.setFrequency(frequency);
}

void Subtractive_synthesizer::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float Subtractive_synthesizer::getSample() {
  sample = (sine.getSample() + square.getSample() + saw.getSample());
  sample /= 3;
  return sample * amplitude;
}

void Subtractive_synthesizer::tick()  {
  sine.tick();
  square.tick();
  saw.tick();
}
