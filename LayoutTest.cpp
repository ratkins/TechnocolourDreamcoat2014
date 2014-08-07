#ifndef LayoutTest_h
#define LayoutTest_h

#include "FastLED.h"
#include "Effect.cpp"

class LayoutTest : public Effect {
  
  private:
    int frame;
  
  public:
    LayoutTest(CRGB *leds) : Effect(leds), frame(0) {}
    
    virtual void draw(int rawPot, int rawMic, bool button) {
        Serial.print("rawPotVal = "); Serial.print(rawPot); Serial.print(", normalised = "); Serial.println(normalisedPotVal(rawPot));
      
        uint8_t hue = 0;
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                pixel(x, y) = CHSV(hue, 255, 255);
            }
            hue += 32;
        }
    }

};

#endif
