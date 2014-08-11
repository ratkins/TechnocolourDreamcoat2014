#ifndef Plasma_h
#define Plasma_h

#include "FastLED.h"
#include "Effect.cpp"

class Plasma : public Effect {
  
  private:
    uint16_t frame;
    CRGBPalette16 palette;
    
    uint8_t paletteIdx = 0;
    static const uint8_t paletteCount = 6;    
    CRGBPalette16 palettes[paletteCount] = {
        CRGBPalette16(RainbowColors_p),
        CRGBPalette16(RainbowStripeColors_p),
        CRGBPalette16(PartyColors_p),
        CRGBPalette16(OceanColors_p),
        CRGBPalette16(ForestColors_p),
        CRGBPalette16(CloudColors_p),  
    };

  
  public:
    Plasma(CRGB *leds) : Effect(leds), paletteIdx(0), frame(0) {
        palette = palettes[paletteIdx];
    }
    
    virtual void draw(int rawPot, int rawMic, bool button) {
        if (button) {
            palette = palettes[++paletteIdx % paletteCount];
            Serial.print("Set palette to "); Serial.print(paletteIdx % paletteCount);
        }
//        palette = RainbowColors_p;
        
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
