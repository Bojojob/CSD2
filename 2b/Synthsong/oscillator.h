#ifndef _OSC_H_
#define _OSC_H_
#include <iostream>
using namespace std;

#define PI_2 6.28318530717959

class Oscillator {
public:
  //Constructor and destructor
  Oscillator();
  ~Oscillator();

  //getters and setters
  void setFrequency(float frequency);
  void setAmplitude(float amplitude);
  void setSamplerate(float samplerate);

  //return the current sample
  float getSample();

protected:
  float amplitude;
  float frequency;
  float phase;
  // contains the current sample
  float sample;
  float samplerate;

};
#endif
