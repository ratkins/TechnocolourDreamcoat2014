#ifndef Effect_h
#define Effect_h

#include "FastLED.h"

#define WIDTH 16
#define HEIGHT 8
#define NUM_LEDS (WIDTH * HEIGHT)

class Effect {
  
  protected:
    CRGB *leds;
    
  public:
    Effect(CRGB *leds) : leds(leds) {}
    
    virtual void draw(uint8_t micVal) = 0;
    
    inXRange(uint16_t x) {
      return x < WIDTH;
    }
    
    inYRange(uint16_t y) {
      return y < HEIGHT;
    }
    
    struct CRGB& pixel(uint16_t x, uint16_t y) {
      if (y & 0x01) {
        // odd y
        return leds[(y * WIDTH) + WIDTH - x - 1];
      } else {
        // even y
        return leds[(y * WIDTH) + x];        

      }
    }
    
};

#endif
