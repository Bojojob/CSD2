#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "oscillator.h"

class Square : public Oscillator {
public:
  Square();
  ~Square();

  void tick();

};
#endif
