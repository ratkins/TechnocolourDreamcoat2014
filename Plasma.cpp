#ifndef Plasma_h
#define Plasma_h

#include "FastLED.h"
#include "Effect.cpp"

class Plasma : public Effect {
  
  private:
    uint16_t frame;
    CRGBPalette16 palette;
  
  public:
    Plasma(CRGB *leds, CRGBPalette16 palette) : Effect(leds), palette(palette), frame(0) {}
    
    virtual void draw(uint8_t micVal) {
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