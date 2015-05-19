#ifndef PICASSO_H
#define PICASSO_H

#include <Arduino.h>
#include <Utils.h>

#define BIT_ON      1
#define BIT_OFF     0
#define BIT_UNDEF   2

#define PCSS_DROP_SHADOW    1
#define PCSS_DASHED         2
#define PCSS_EMPTY          4

class Picasso {
  public:
  Picasso (unsigned int width, unsigned int height);
  
  void createCanvas (unsigned int width, unsigned int height);
  void pixel (unsigned int x, unsigned int y);
  void empty (unsigned int x, unsigned int y);
  void line (unsigned int x1, unsigned int y1,
             unsigned int x2, unsigned int y2,
             unsigned int flags);
  void rect (unsigned int x, unsigned int y,
             unsigned int width, unsigned int height,
             unsigned int flags);
  void circle (unsigned int x, unsigned int y, unsigned int r);
  
  void clear(void);
  
  /*
   * TODO: Try optimising this, by polling only changed fragments. (3-state bit map ON | OFF | UNDEF).
   */
  byte** getCanvas (void);
  
  private:
  byte** canvas;
  unsigned int canvas_width;
  unsigned int canvas_height;
  
};

#endif