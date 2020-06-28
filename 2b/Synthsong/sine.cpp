#include "sine.h"
#include "math.h"

Sine::Sine() : Oscillator() {
}

Sine::~Sine() {
}

void Sine::tick() {

  phase += frequency / samplerate;
  sample = sin(M_PI * 2 * phase) * amplitude;

}
