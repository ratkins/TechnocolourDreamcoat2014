#ifndef ChaseTest_h
#define ChaseTest_h

#include "FastLED.h"
#include "Effect.cpp"

class ChaseTest : public Effect {
  
  private:
    int frame;
  
  public:
    ChaseTest(CRGB *leds) : Effect(leds), frame(0) {}
    
    virtual void draw(uint8_t micVal) {
      leds[frame++ % NUM_LEDS] = CRGB::White;
    }

};

#endif
