#ifndef ChaseTest_h
#define ChaseTest_h

#include "FastLED.h"
#include "Effect.cpp"

class ChaseTest : public Effect {
  
  private:
    int frame;
  
  public:
    ChaseTest(CRGB *leds) : Effect(leds), frame(0) {}
    
    void draw(int rawPot, int rawMic, bool button) {
      leds[frame++ % NUM_LEDS] = CRGB::White;
    }

};

#endif
