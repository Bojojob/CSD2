#include <iostream>
#include "subtractive_synthesizer.h"

subtractive_synthesizer::subtractive_synthesizer()  {
  amplitude = 1.0;
  sample = 0;

  Sine sine;
  Square square;
  Saw saw;
}

subtractive_synthesizer::~subtractive_synthesizer()  {

}

void subtractive_synthesizer::setSamplerate(float samplerate) {
  this->samplerate = samplerate;

  sine.setSamplerate(samplerate);
  square.setSamplerate(samplerate);
  saw.setSamplerate(samplerate);
}

void subtractive_synthesizer::setFrequency(float frequency) {
  this->frequency = frequency;

  sine.setFrequency(frequency);
  square.setFrequency(frequency);
  saw.setFrequency(frequency);
}

void subtractive_synthesizer::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float subtractive_synthesizer::getSample() {
  sample = (sine.getSample() + square.getSample() + saw.getSample());
  sample /= 3;
  return sample * amplitude;
}

void subtractive_synthesizer::tick()  {
  sine.tick();
  square.tick();
  saw.tick();
}
