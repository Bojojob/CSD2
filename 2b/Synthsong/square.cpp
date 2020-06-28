#include "square.h"
#include "math.h"

Square::Square() : Oscillator() {
}

Square::~Square() {
}

void Square::tick() {
  phase += frequency / samplerate;
  sample = sin(M_PI * 2 * phase);

  if (sample >= 0.0)
    sample = amplitude;
  else
    sample = -amplitude;

}
