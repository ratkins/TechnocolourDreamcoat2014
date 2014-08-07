#ifndef FireEffect_h
#define FireEffect_h

#include "FastLED.h"
#include "Effect.cpp"

#define COOLING 70
#define SPARKING 120

class FireEffect : public Effect {
  
  private:
    uint8_t column;
    CRGBPalette16 palette;
    uint8_t heat[HEIGHT];
  
  public:
    FireEffect(CRGB *leds, uint8_t column, CRGBPalette16 palette) : Effect(leds), column(column), palette(palette) {
    }
    
    virtual void draw(int rawPot, int rawMic, bool button) {
      random16_add_entropy(random());

      // Step 1.  Cool down every cell a little  
      for (int i = 0; i < HEIGHT; i++) {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / HEIGHT) + 2));
      }
  
      // Step 2.  Heat from each cell drifts 'up' and diffuses a little
      for (int k = HEIGHT - 1; k > 1; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
      }
      
      // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
     if (random8() < normalisedMicVal(rawMic, rawPot)) {
       int y = random8(5);
       heat[y] = qadd8(heat[y], random8(160, 255));
     }

     // Step 4.  Map from heat cells to LED colors
     for(int j = 0; j < HEIGHT; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
       byte colorindex = scale8(heat[j], 240);
       pixel(column, j) = ColorFromPalette(palette, colorindex);
       pixel(column + 12, j) = ColorFromPalette(palette, colorindex);       
       pixel(column + 24, j) = ColorFromPalette(palette, colorindex);              
     }
   }

};

#endif
