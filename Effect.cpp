#ifndef Effect_h
#define Effect_h

#include "FastLED.h"

#define WIDTH 36
#define HEIGHT 20
#define NUM_LEDS 640 // 38.4A, motherfuckers

class Effect {
  
  protected:
    CRGB *leds;
    CRGB deadPixel;
    int columnHeights[WIDTH] = {
        20, 20, 20, 20, 18, 18, 18, 14, 12, 
        12, 14, 20, 20, 20, 20, 18, 18, 18, 
        18, 18, 18, 20, 20, 20, 20, 14, 12, 
        12, 14, 18, 18, 18, 20, 20, 20, 20
    };
    
  public:
    Effect(CRGB *leds) : leds(leds), deadPixel(CRGB::Black) {}
    
    virtual void draw(uint8_t micVal) = 0;
    
    bool visible(int16_t x, int16_t y) {
      return x >= 0 && y >= 0 && x < WIDTH && y < columnHeights[x];
    }
    
    struct CRGB& maxY(int16_t x) {
        return columnHeights[x];
    }
    
    struct CRGB& pixel(int16_t x, int16_t y) {
        if (visible(x, y)) {
            uint8_t sum = 0;
            for (int i = 0; i < x; i++) {
                sum += columnHeights[i];
            }
            if (x & 0x01) {
                return leds[sum + columnHeights[x] - y - 1];
            } else {
                return leds[sum + y];
            }
        } else {
            return deadPixel;
        } 
    }
    
};

#endif
