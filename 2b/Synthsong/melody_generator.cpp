#include <iostream>
#include <thread>
#include <chrono>
#include "melody_generator.h"


MelodyGenerator::MelodyGenerator()  {

}

MelodyGenerator::~MelodyGenerator()  {

}

void MelodyGenerator::setFrequency(float frequency)  {
  this->frequency = frequency;
}

void MelodyGenerator::setNoteAmount(int noteAmount) {
  this->noteAmount = noteAmount;
}

float MelodyGenerator::getFrequency()  {
  return frequency;
}

void MelodyGenerator::generateMelody()  {
  std::cout << "Generating a melody that is " << noteAmount << " notes long.\n";
  for(int i = 0; i < noteAmount; i++) {
    setFrequency(rand() % 500 + 100);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout<<"Done.\n";
}
