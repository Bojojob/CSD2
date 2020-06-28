#ifndef _MELODY_GENERATOR_H_
#define _MELODY_GENERATOR_H_
#include <vector>

class MelodyGenerator {
public:
  MelodyGenerator();
  ~MelodyGenerator();

  void setFrequency(float frequency);
  void setNoteAmount(int noteAmount);
  void getNote();
  float getFrequency();
  void generateMelody();

protected:
  int noteAmount;
  float frequency;
  //enter pitch values for Hirajoshi scale into the vector
  std::vector<float> scale{261.63, 329.63, 369.99, 392.0, 493.88, 523.25};

};
#endif
