#ifndef Starfield_h
#define Starfield_h

#include "FastLED.h"
#include "Effect.cpp"

#define MAX_STARS (WIDTH * HEIGHT / 10)

struct Star {
    float x, y;
    uint8_t plane;
};

const uint8_t planes[] = {255, 192, 128};

class Starfield : public Effect {
  
  private:
    int frame;
    Star stars[MAX_STARS];
  
  public:
    Starfield(CRGB *leds) : Effect(leds, "Starfield"), frame(0) {
        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].x = random8(WIDTH);
            stars[i].y = random8(HEIGHT);
            stars[i].plane = random8(3);
        }
    }
    
    void draw(EffectControls controls) {
        for (int i = 0; i < MAX_STARS; i++) {
            Serial.print("star["); Serial.print(i); Serial.print("] x/y = "); Serial.print(stars[i].x); Serial.print("/"); Serial.println(stars[i].y);
            stars[i].x += (1 + (float)stars[i].plane) * 0.15;
            
            // Check if our star is off the right of the screen
            if (stars[i].x > WIDTH) {
              
                // If so, put it back on the left
                stars[i].x = 0;

                // and randomly change the y position
                stars[i].y = random8(HEIGHT);
            }
            pixel(stars[i].x, stars[i].y) = CRGB(planes[stars[i].plane], planes[stars[i].plane], planes[stars[i].plane]);
        }
    }

};

#endif

