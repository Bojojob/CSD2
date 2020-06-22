#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "synthesizer.h"



#define PI_2 6.28318530717959

int main(int argc,char **argv)
{
  JackModule jack;
  jack.init(argv[0]);
  double samplerate = jack.getSamplerate();
/*
  Sine sine;
  sine.setFrequency(880);
  sine.setSamplerate(samplerate);

  Square square;
  square.setFrequency(440);
  square.setSamplerate(samplerate);


  Saw saw;
  saw.setFrequency(660);
  saw.setSamplerate(samplerate);
*/

  Synthesizer synthesizer;
  synthesizer.setSamplerate(samplerate);
  synthesizer.setFrequency(440);



  //assign a function to the JackModule::onProces
  jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = synthesizer.getSample();
      synthesizer.tick();
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
    }
  }

  //end the program
  return 0;
} // main()
