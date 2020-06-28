#ifndef _MELODY_GENERATOR_H_
#define _MELODY_GENERATOR_H_

class MelodyGenerator {
public:
  MelodyGenerator();
  ~MelodyGenerator();

  void setFrequency(float frequency);
  void setNoteAmount(int noteAmount);
  float getFrequency();
  void generateMelody();

protected:
  int noteAmount;
  float frequency;

};
#endif
