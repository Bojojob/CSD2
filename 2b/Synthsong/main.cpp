#include <iostream>
#include <thread>
#include <climits>
#include "math.h"
#include "jack_module.h"
#include "subtractive_synthesizer.h"
#include "fm_synthesizer.h"
#include "melody_generator.h"

#define PI_2 6.28318530717959

//switches used to mute and unmute the synths
bool subSynthSwitch = false;
bool fmSynthSwitch = true;
//for storing input
int input;

int main(int argc,char **argv)
{
  JackModule jack;
  jack.init(argv[0]);
  double samplerate = jack.getSamplerate();

  //initialize the synthesizers and the melody generator
  Subtractive_synthesizer subSynth;
  subSynth.setAmplitude(0);
  subSynth.setSamplerate(samplerate);
  subSynth.setFrequency(220);

  Fm_synthesizer fmSynth;
  fmSynth.setSamplerate(samplerate);
  fmSynth.setFmRatio(3);
  fmSynth.setFmAmount(1500);

  //sets frequency for the melodyGen so the synths produce sound on startup
  MelodyGenerator melodyGen;
  melodyGen.setFrequency(261.63);


  //assign a function to the JackModule::onProces
  jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = (subSynth.getSample() + fmSynth.getSample());
      //the frequency of the fm synth must be updated at audio rate
      fmSynth.setFrequency(melodyGen.getFrequency());
      subSynth.setFrequency(melodyGen.getFrequency());
      fmSynth.updateFrequency();
      fmSynth.tick();
      subSynth.tick();
    }

    return 0;
  };

  jack.autoConnect();

  //information for the user
  std::cout << "\nPress 'm' to generate a melody.\n";
  std::cout << "\nPress 'n' to change the length of the melody.\n";
  std::cout << "\nPress 's' to mute and unmute the subtractive Synthesizer.\n";
  std::cout << "\nPress 'f' to mute and unmute the fm Synthesizer.\n";
  std::cout << "\nPress 'r' to generate a random fm patch.\n";
  std::cout << "\nPress 'q' to quit the program.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'm':
      melodyGen.generateMelody();
      break;
      case 'n':
        std::cout << "Enter a number,";
        std::cout << "\nThis indicates how many notes will be generated.\n";
        std::cin >> input;
        while (!std::cin.good()) {
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          std::cout << "That's not what I was looking for...\n";
        }
        melodyGen.setNoteAmount(input);
        break;
      case 's':
        subSynthSwitch = !subSynthSwitch;
        subSynth.setAmplitude(subSynthSwitch);
        break;
      case 'f':
        fmSynthSwitch = !fmSynthSwitch;
        fmSynth.setAmplitude(fmSynthSwitch);
        break;
      case 'r':
        fmSynth.setFmRatio(rand() % 8);
        fmSynth.setFmAmount(rand() % 10000);
        break;
        case 'q':
        running = false;
        jack.end();
        break;
    }
  }

  //end the program
  return 0;
}
