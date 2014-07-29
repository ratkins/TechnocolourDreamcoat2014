#ifndef AdvancingPaletteEffect_h
#define AdvancingPaletteEffect_h

#include "FastLED.h"
#include "Effect.cpp"

class AdvancingPaletteEffect : public Effect {
  
  private:
    uint8_t colourIndex;
    CRGBPalette16 palette;
  
  public:
    AdvancingPaletteEffect(CRGB *leds, CRGBPalette16 palette) : Effect(leds), 
      palette(palette), 
      colourIndex(0) {}
    
    virtual void draw(uint8_t micVal) {
      for (int i = 0; i < HEIGHT; i++) {     
        pixel(0, i) = ColorFromPalette(palette, colourIndex + i);
      }
      colourIndex++;
    }

};

#endif
