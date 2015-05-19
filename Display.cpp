#include <Display.h>
#include <Const.h>

Display::Display () {
  display_width = 0;
  display_height = 0;
  
  draw = new Picasso(0, 0);
};

Display::Display (unsigned short width, unsigned short height) {
  display_width = width;
  display_height = height;
  
  draw = new Picasso(display_width, display_height);
};

void Display::init (void) {
  /*
   * Initialize display pins.
   */
  Serial.println("Display --test");
};

void Display::clear (void) {
  /*
   * Empty display.
   */
};

void Display::write (byte dc, byte data) {
  /*
   * Turn display into Data/!Command mode.
   * Write `data` to the display.
   */
};

void Display::xy (unsigned short x, unsigned short y) {
  /*
   * Move display cursor to x/y position.
   */
};

void Display::drawFrame (void) {
  /*
   * Draw next frame.
   */
};

unsigned short Display::getWidth (void) {
  return display_width;
};

unsigned short Display::getHeight (void) {
  return display_height;
};