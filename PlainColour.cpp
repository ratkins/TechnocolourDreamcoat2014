#ifndef PlainColour_h
#define PlainColour_h

#include "FastLED.h"
#include "Effect.cpp"

class PlainColour : public Effect {
  
  private:
    CRGB colour;
  
  public:
    PlainColour(CRGB *leds, CRGB colour) : Effect(leds), colour(colour) {}
    
    virtual void draw(int rawPot, int rawMic, bool button) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = colour;
      }
    }

};

#endif
