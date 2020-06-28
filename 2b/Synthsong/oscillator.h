#ifndef _OSC_H_
#define _OSC_H_

#define PI_2 6.28318530717959

class Oscillator {
public:
  Oscillator();
  ~Oscillator();

  void setFrequency(float frequency);
  void setAmplitude(float amplitude);
  void setSamplerate(float samplerate);

  float getSample();

protected:
  float amplitude;
  float frequency;
  float phase;
  float sample;
  float samplerate;

};
#endif
