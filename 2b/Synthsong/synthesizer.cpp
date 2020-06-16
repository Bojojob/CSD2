#include <iostream>
#include "synthesizer.h"

Synthesizer::Synthesizer(float samplerate)  {
  this->samplerate = samplerate;

  Sine sine;
  Square square;
  Saw saw;

}

Synthesizer::~Synthesizer()  {

}

void Synthesizer::setFrequency(float frequency) {
  this->frequency = frequency;
  sine.setFrequency(frequency);
}

void Synthesizer::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float Synthesizer::getSample() {
  return ((sine.getSample() + square.getSample() + saw.getSample()) / 3);
}
