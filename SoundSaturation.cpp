#ifndef SoundSaturation_h
#define SoundSaturation_h

#include "FastLED.h"
#include "Effect.cpp"

class SoundSaturation : public Effect {
  
  private:
    uint8_t brightness;
  
  public:
    SoundSaturation(CRGB *leds) : Effect(leds), brightness(0) {}
    
    virtual void draw(int rawPot, int rawMic, bool button) {
        if (normalisedMicVal(rawMic, rawPot) > SOUND_THRESHOLD) {
            brightness = 255;
        }
        for (int i = 0; i < NUM_LEDS; i++) {
            if (leds[i]) {          
                nblend(leds[i], CRGB::White, brightness);
            }
        }
        brightness = constrain(brightness - 32, 0, 255);
    }

};

#endif
