#ifndef NK5110_H
#define NK5110_H

#include <Display.h>
#include <Arduino.h>
#include <Const.h>

#define NK5110_WIDTH            84
#define NK5110_HEIGHT           48

#define NK5110_INSTRUCTION_BASIC  0x00
#define NK5110_INSTRUCTION_EXT    0x01

#define NK5110_POWER_DOWN_ENABLED  0x04
#define NK5110_POWER_DOWN_DISABLED 0x00

#define NK5110_BASIC_CONTRAST 0x30

#define NK5110_TEMP_0 0x00
#define NK5110_TEMP_1 0x01
#define NK5110_TEMP_2 0x10
#define NK5110_TEMP_3 0x11

#define NK5110_BIAS_140 0x04
#define NK5110_BIAS_148 0x03

#define NK5110_DSP_BLANK  0x00
#define NK5110_DSP_NORMAL 0x04
#define NK5110_DSP_BLACK  0x01
#define NK5110_DSP_INVERT 0x05

#define NK5110_FUNC_SET_C  0x20
#define NK5110_CONTRAST_C  0x80
#define NK5110_TEMP_COE_C  0x04
#define NK5110_BIAS_C      0x10
#define NK5110_DSP_C       0x08

#define NK5110_SET_X       0x80
#define NK5110_SET_Y       0x40

class NK5110 : public Display {
  public:
  NK5110 ();
  
  void init (void);
  void reset (void);
  void clear (void);
  void write (byte dc, byte data);
  void xy (unsigned short x, unsigned short y);
  
  /*
   * Configuration
   */
  void setInstructionMode (byte value);
  void setPowerDownMode (byte value);
  void setContrast (byte value);
  void setTemperatureCoefficent (byte value);
  void setBiasMode (byte value);
  void setDisplayMode (byte value);
  
  /*
   * Drawing
   */
  void drawFrame (void);
  
  private:
  byte instruction_set = NK5110_INSTRUCTION_BASIC;
  byte power_down_mode = NK5110_POWER_DOWN_DISABLED;
};

#endif