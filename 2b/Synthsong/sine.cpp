#include "sine.h"
#include "math.h"

Sine::Sine() : Oscillator() {
}

Sine::~Sine() {
}

void Sine::tick() {

  phase += frequency / samplerate;
  sample = amplitude * (sin(phase * PI_2));
}
