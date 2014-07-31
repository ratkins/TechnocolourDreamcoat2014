#ifndef LayoutTest_h
#define LayoutTest_h

#include "FastLED.h"
#include "Effect.cpp"

class LayoutTest : public Effect {
  
  private:
    int frame;
  
  public:
    LayoutTest(CRGB *leds) : Effect(leds), frame(0) {}
    
    virtual void draw(uint8_t micVal) {
        uint8_t hue = 0;
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                pixel(x, y) = CHSV(hue, 255, 255);
            }
            hue += 32;
        }
//        for (int y = 0; y < maxY(WIDTH - 1); y++) {
//            pixel(WIDTH - 1, y) = CRGB::Red;
//        }
//        for (int x = WIDTH - 1; x >= 0; x--) {
//            pixel(x, maxY(x)) = CRGB::Green;
//        }
//        for (int y = maxY(0); y >=0; y--) {
//            pixel(0, y) = CRGB::Blue;
//        }
    }

};

#endif
