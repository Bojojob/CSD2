#include <iostream>
#include <thread>
#include <chrono>
#include "melody_generator.h"
#include <iostream>


MelodyGenerator::MelodyGenerator()  {
  //set seed for random number generation
  srand((unsigned int)time(NULL));
  //noteAmount is set to 4 by default
  noteAmount = 8;
}

MelodyGenerator::~MelodyGenerator()  {

}

void MelodyGenerator::setFrequency(float frequency)  {
  this->frequency = frequency;
}

void MelodyGenerator::setNoteAmount(int noteAmount) {
  this->noteAmount = noteAmount;

  std::cout << "Melody set to " << noteAmount << " note length.\n";
}

void MelodyGenerator::getNote() {

}

float MelodyGenerator::getFrequency()  {
  return frequency;
}

//generates melody by picking random notes from the scale
void MelodyGenerator::generateMelody()  {
  std::cout << "Generating a melody that is " << noteAmount << " notes long.\n";
  for(int i = 0; i < noteAmount; i++) {
    float pitch = scale[rand() % 5];
    std::cout << "Set pitch to " << pitch << " Hz\n";
    setFrequency(pitch);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
  std::cout<<"Done.\n";
}
