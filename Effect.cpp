#ifndef Effect_h
#define Effect_h

#include "FastLED.h"

#define FUCK

class Effect {
  
  protected:
    CRGB *leds;
    uint16_t width, height;
    
  public:
    Effect(CRGB *leds, uint16_t width, uint16_t height) : leds(leds), width(width), height(height) {}
    
    virtual void draw(uint8_t micVal) = 0;
    
    struct CRGB& pixel(uint16_t x, uint16_t y) {
      if (x & 0x01) {
        return leds[(x * width) + x - y - 1];
      } else {
        return leds[(x * width) + y];
      }
    }
    
};

#endif
