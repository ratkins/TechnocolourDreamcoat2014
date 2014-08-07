#ifndef Scintillate_h
#define Scintillate_h

#include "FastLED.h"
#include "Effect.cpp"

#define DENSITY (NUM_LEDS/40)

class Scintillate : public Effect {
  
  private:
    
  public:
    Scintillate(CRGB *leds) : Effect(leds) {}
    
    virtual void draw(int rawPot, int rawMic, bool button) {
        for (int i = 0; i < NUM_LEDS; i++) {
            if (DENSITY > random(NUM_LEDS)) {
                leds[i] = CRGB::White;
            }
        }
    }
    
};

#endif
