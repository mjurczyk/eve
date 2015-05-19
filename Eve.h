#ifndef EVE_PROJECT_H
#define EVE_PROJECT_H

#include <Arduino.h>
#include <Display.h>
#include <Nokia-5110.h>

class EVE {
  public:
  
  void init();
  void tick();
  
  private:
  Display *display;
};

#endif