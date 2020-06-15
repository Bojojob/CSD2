#include "oscillator.h"

Oscillator::Oscillator() {
}

Oscillator::~Oscillator() {
}

void Oscillator::setFrequency(float frequency) {
  this->frequency = frequency;
}

void Oscillator::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float Oscillator::getAmplitude() {
  return amplitude;
}

float Oscillator::getSample() {
  return sample;
}
