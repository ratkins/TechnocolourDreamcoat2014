#ifndef Plasma_h
#define Plasma_h

#include "FastLED.h"
#include "Effect.cpp"

class Plasma : public Effect {
  
  private:
    uint16_t frame;
    CRGBPalette16 palette;
    
    uint8_t paletteIdx = 0;
//    CRGBPalette16 *palettes[6] = {
//        &RainbowColors_p,
//        &RainbowStripeColors_p,
//        &PartyColors_p,
//        &OceanColors_p,
//        &ForestColors_p,
//        &CloudColors_p,  
//    };
    uint8_t paletteCount = 6;
  
  public:
    Plasma(CRGB *leds) : Effect(leds), paletteIdx(0), frame(0) {}
    
    virtual void draw(int rawPot, int rawMic, bool button) {
//        if (button) {
//            palette = *palettes[++paletteIdx % paletteCount];
//        }
        palette = RainbowColors_p;
        
        frame += 100;
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                int16_t v = 0;
                uint16_t wibble = sin8(frame);
                v += sin16(x * wibble * 8 + frame);
                v += cos16(y * (128 - wibble) * 4 + frame);
                v += sin16(y * x * cos8(-frame) / 2);
                
                pixel(x, y) = ColorFromPalette(palette, (v >> 8) + 127);
            }
        }      
    }
    
    uint8_t sin8(uint16_t x) {
        return (sin16(x) >> 8) + 128;
    }
    
    uint8_t cos8(uint16_t x) {
        return (cos16(x) >> 8) + 128;
    }    

};

#endif
