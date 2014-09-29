#ifndef Scintillate_h
#define Scintillate_h

#include "FastLED.h"
#include "Effect.cpp"

#define DENSITY (NUM_LEDS/40)

class Scintillate : public Effect {
  
  private:
    bool soundReactive;
    uint8_t brightness;
    
  public:
    Scintillate(CRGB *leds) : Effect(leds), soundReactive(false), brightness(0) {}
    
    virtual void draw(EffectControls controls) {
        soundReactive = controls.button ? !soundReactive : soundReactive;
        
        if (normalisedMicVal(controls.rawMic, controls.rawPot) > SOUND_THRESHOLD) {
            brightness = 0;
        }
        
        for (int i = 0; i < NUM_LEDS; i++) {
            if (DENSITY > random(NUM_LEDS)) {
                if (soundReactive) {
                    nblend(leds[i], CRGB::White, brightness);                    
                } else {
                    leds[i] = CRGB::White;
                }
            }
        }
        brightness = constrain(brightness + 16, 0, 255);        
        
    }
    
};

#endif

