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
    
    virtual void draw(int rawPot, int rawMic, bool button) = 0;
    
    bool visible(int16_t x, int16_t y) {
      return x >= 0 && y >= 0 && x < WIDTH && y < columnHeights[x];
    }
    
    int16_t maxY(int16_t x) {
        return columnHeights[x];
    }
    
    struct CRGB& pixel(int16_t x, int16_t y) {

        if (visible(x, y)) {
//            Serial.print("pixel("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.println(") - visible");
            uint16_t sum = 0;
            for (int i = 0; i < x; i++) {
              sum += columnHeights[i];
            }

            if (x & 0x01) {
//                Serial.print("odds, returning leds index "); Serial.println(sum + columnHeights[x] - y - 1);
                return leds[sum + columnHeights[x] - y - 1];
            } else {
//                Serial.print("even, returning leds index "); Serial.println(sum + y);              
                return leds[sum + y];
            }
        } else {
//            Serial.print("pixel("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.println(") - deadPixel");
            return deadPixel;
        } 
    }
    
    uint8_t normalisedPotVal(int rawPotVal) {
        uint8_t normalised = map(rawPotVal, 0, 1023, 0, 255);
        return normalised;
    }

    uint8_t normalisedMicVal(int rawMicVal, int rawPotVal) {
        uint8_t normalised = map((rawMicVal - 400) * rawPotVal, 1023 - 400, 1024 * 1024, 0, 255);
        return normalised;
    }
    
};

#endif
