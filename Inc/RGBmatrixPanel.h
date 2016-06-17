#include "Adafruit_GFX.h"
#include "gamma.h"
#include "stm32f7xx_hal.h"
//#include "stm32f746xx.h"

class RGBmatrixPanel : public Adafruit_GFX{

 public:

  // Constructor for 16x32 panel:
  RGBmatrixPanel(uint16_t a, uint16_t b, uint16_t c,
		  uint16_t sclk, uint16_t latch, uint16_t oe, bool dbuf);

  // Constructor for 32x32 panel (adds 'd' pin):
  RGBmatrixPanel(uint16_t a, uint16_t b, uint16_t c, uint16_t d,
		  uint16_t sclk, uint16_t latch, uint16_t oe, bool dbuf, uint16_t width=32);

  void
    begin(void),
    drawPixel(int16_t x, int16_t y, uint16_t c),
    fillScreen(uint16_t c),
    updateDisplay(void),
    swapBuffers(bool),
    dumpMatrix(void);
  uint8_t
    *backBuffer(void);
  uint16_t
    Color333(uint8_t r, uint8_t g, uint8_t b),
    Color444(uint8_t r, uint8_t g, uint8_t b),
    Color888(uint8_t r, uint8_t g, uint8_t b),
    Color888(uint8_t r, uint8_t g, uint8_t b, bool gflag),
    ColorHSV(long hue, uint8_t sat, uint8_t val, bool gflag);

 private:

  uint8_t         *matrixbuff[2];
  uint8_t          nRows;
  volatile uint8_t backindex;
  volatile bool swapflag;

  // Init/alloc code common to both constructors:
  void init(uint16_t rows, uint16_t a, uint16_t b, uint16_t c,
		  uint16_t sclk, uint16_t latch, uint16_t oe, bool dbuf,
		  uint16_t width);


  void INTRP_TIM3_Init(void);

  // PORT register pointers, pin bitmasks, pin numbers:
  /*volatile uint8_t
    *latport, *oeport, *addraport, *addrbport, *addrcport, *addrdport;*/
  uint8_t
    sclkpin, latpin, oepin, addrapin, addrbpin, addrcpin, addrdpin,
    _sclk, _latch, _oe, _a, _b, _c, _d;

  // Counters/pointers for interrupt handler:
  volatile uint8_t row, plane;
  volatile uint8_t *buffptr;
};

