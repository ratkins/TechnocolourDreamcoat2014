#ifndef Perlin_h
#define Perlin_h

#include "FastLED.h"
#include "Effect.cpp"

#define MAX_DIMENSION WIDTH

class Perlin : public Effect {
  
  private:
    uint8_t hue;
    uint16_t speed;
    uint16_t scale;    
    uint16_t x;
    uint16_t y;
    uint16_t z;
    
    uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];
  
  public:
    Perlin(CRGB *leds) : Effect(leds), hue(0), speed(16), scale(30) {
        x = random16();
        y = random16();
        z = random16();
    }
    
    virtual void draw(int rawPot, int rawMic, bool button) {
        fillnoise8();
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                // We use the value at the (i,j) coordinate in the noise
                // array for our brightness, and the flipped value from (j,i)
                // for our pixel's hue.
//                pixel(i, j) = CHSV(noise[j][i], 255, noise[i][j]);
  
                // You can also explore other ways to constrain the hue used, like below
                pixel(i, j) = CHSV(hue + (noise[j][i]>>2), 255, noise[i][j]);
            }
        }
        hue++;
    }
    
    void fillnoise8() {
        for (int i = 0; i < MAX_DIMENSION; i++) {
            int ioffset = scale * i;
            for (int j = 0; j < MAX_DIMENSION; j++) {
                int joffset = scale * j;
                noise[i][j] = inoise8(x + ioffset, y + joffset, z);
            }
        }
        z += speed;
    }
};

#endif
