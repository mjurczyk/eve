#include <Nokia-5110.h>

NK5110::NK5110 () : Display(NK5110_WIDTH, NK5110_HEIGHT) { /* ... */ };

void NK5110::init (void) {
  pinMode(DSP_PIN_CE,  OUTPUT);
  pinMode(DSP_PIN_RST, OUTPUT);
  pinMode(DSP_PIN_DC,  OUTPUT);
  pinMode(DSP_PIN_DIN, OUTPUT);
  pinMode(DSP_PIN_CLK, OUTPUT);
  
  reset();
  
  setInstructionMode(NK5110_INSTRUCTION_EXT);
  setContrast(NK5110_BASIC_CONTRAST);
  setTemperatureCoefficent(NK5110_TEMP_0);
  setBiasMode(NK5110_BIAS_140);
  setInstructionMode(NK5110_INSTRUCTION_BASIC);
  setDisplayMode(NK5110_DSP_NORMAL);
};

void NK5110::reset (void) {
  digitalWrite(DSP_PIN_RST, LOW);
  digitalWrite(DSP_PIN_RST, HIGH);
};

void NK5110::clear (void) {
  /*
   * Empty display.
   */
};

void NK5110::write (byte dc, byte data) {
  digitalWrite(DSP_PIN_DC, dc);
  digitalWrite(DSP_PIN_CE, LOW);
  shiftOut(DSP_PIN_DIN, DSP_PIN_CLK, MSBFIRST, data);
  digitalWrite(DSP_PIN_CE, HIGH);
};

void NK5110::xy (unsigned short x, unsigned short y) {
  /*
   * Move display cursor to x/y position.
   */
  x = x % 84;
  y = y % 6;
  
  write(DSP_C, NK5110_SET_X | x);
  write(DSP_C, NK5110_SET_Y | y);
};

void NK5110::setInstructionMode (byte value) {
  instruction_set = value;
  
  write(DSP_C, 
        NK5110_FUNC_SET_C | 
        power_down_mode |
        instruction_set
       );
};

void NK5110::setPowerDownMode (byte value) {
  power_down_mode = value;
  
  write(DSP_C, 
        NK5110_FUNC_SET_C | 
        power_down_mode |
        instruction_set);
};

void NK5110::setContrast (byte value) {
  write(DSP_C,
        NK5110_CONTRAST_C |
        value);
};

void NK5110::setTemperatureCoefficent (byte value) {
  write(DSP_C,
        NK5110_TEMP_COE_C |
        value);
};

void NK5110::setBiasMode (byte value) {
  write(DSP_C,
        NK5110_BIAS_C |
        value);
};

void NK5110::setDisplayMode (byte value) {
  write(DSP_C,
        NK5110_DSP_C |
        value);
};

void NK5110::drawFrame (void) {
  byte** frame = draw->getCanvas();

  unsigned int x, y;
  unsigned int rows = NK5110_HEIGHT / 8;
  
  xy(0, 0);
  
  for (y = 0; y < rows; y++) {
    for (x = 0; x < NK5110_WIDTH; x++) {
      write(DSP_D, frame[y][x]);
    }
  }
};