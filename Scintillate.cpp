#ifndef Scintillate_h
#define Scintillate_h

#include "FastLED.h"
#include "Effect.cpp"

#define DENSITY (NUM_LEDS/40)

class Scintillate : public Effect {
  
  private:
    bool soundReactive;
    uint8_t value;
    
  public:
    Scintillate(CRGB *leds) : Effect(leds), soundReactive(false), value(255) {}
    
    virtual void draw(int rawPot, int rawMic, bool button) {
        soundReactive = button ? !soundReactive : soundReactive;
        
        if (normalisedMicVal(rawMic, rawPot) > SOUND_THRESHOLD) {
            value = 0;
        }
        
        value = constrain(value + 32, 0, 255);        
        for (int i = 0; i < NUM_LEDS; i++) {
            if (DENSITY > random(NUM_LEDS)) {
                if (soundReactive) {
                    leds[i] = CHSV(0, 0, value);
                } else {
                    leds[i] = CRGB::White;
                }
            }
        }
    }
    
};

#endif
