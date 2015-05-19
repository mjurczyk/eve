#include <Eve.h>

void EVE::init () {
  display = new NK5110();
  display->init();
};
#include <math.h>
void EVE::tick () {
  display->draw->clear();
  
  
  
  display->drawFrame();
};