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
      leds[1] = CRGB::Red;
      leds[2] = CRGB::Green;
      leds[3] = CRGB::Blue;
      
      // origin
      pixel(0, 0) = CRGB::White;
      
      // bottom left
      pixel(WIDTH - 1, 0) = CRGB::Red;
      
      // top left
      pixel(WIDTH - 1, HEIGHT - 1) = CRGB::Green;
      
      // top right
      pixel(0, HEIGHT - 1) = CRGB::Blue;
    }

};

#endif
