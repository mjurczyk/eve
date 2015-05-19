#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Picasso.h>

/*
 * TODO:
 * - Add aspect ratio scaling, for more natural circles etc.
 */

class Display {
  public:
  Display ();
  Display (unsigned short width, unsigned short height);
  
  virtual void init (void);
  virtual void clear (void);
  virtual void write (byte dc, byte data);
  virtual void xy (unsigned short x, unsigned short y);
  virtual void drawFrame (void);
  
  unsigned short getWidth (void);
  unsigned short getHeight (void);
  
  Picasso *draw;
  
  protected:
  unsigned short display_width;
  unsigned short display_height;
  
  private:
};

#endif