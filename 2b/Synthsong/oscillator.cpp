#include "oscillator.h"

Oscillator::Oscillator() {
  amplitude = 1.0;
  sample = 0;
  phase = 0;
}

Oscillator::~Oscillator() {

}

void Oscillator::setFrequency(float frequency) {
  this->frequency = frequency;
}

void Oscillator::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

void Oscillator::setSamplerate(float samplerate)  {
  this->samplerate = samplerate;
}

float Oscillator::getSample() {
  return sample;
}
