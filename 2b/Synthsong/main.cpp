#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "subtractive_synthesizer.h"
#include "fm_synthesizer.h"


#define PI_2 6.28318530717959

bool subSynthSwitch = true;
bool fmSynthSwitch = false;

int main(int argc,char **argv)
{
  JackModule jack;
  jack.init(argv[0]);
  double samplerate = jack.getSamplerate();

  subtractive_synthesizer subSynth;
  subSynth.setSamplerate(samplerate);
  subSynth.setFrequency(220);

  fm_synthesizer fmSynth;
  fmSynth.setSamplerate(samplerate);
  fmSynth.setFrequency(440);
  fmSynth.setFmRatio(4);
  fmSynth.setFmAmount(2000);
  fmSynth.setAmplitude(0);

  //assign a function to the JackModule::onProces
  jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = (subSynth.getSample() + fmSynth.getSample());
      fmSynth.updateFrequency();
      subSynth.tick();
      fmSynth.tick();
    }

    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        jack.end();
        break;
      case 's':
        subSynthSwitch = !subSynthSwitch;
        subSynth.setAmplitude(subSynthSwitch);
        fmSynthSwitch = !fmSynthSwitch;
        fmSynth.setAmplitude(fmSynthSwitch);
        break;
    }
  }

  //end the program
  return 0;
} // main()
