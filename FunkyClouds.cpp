#ifndef FunkyClouds_h
#define FunkyClouds_h

#include "FastLED.h"
#include "Effect.cpp"

class FunkyClouds : public Effect {
  
  private:
    int frame;
    
    struct timer {
        unsigned long tact;
        unsigned long lastMillis;
        unsigned long count;
        int delta;
        byte up;
        byte down;
    };
    timer multiTimer[7];
    int timers = sizeof(multiTimer) / sizeof(multiTimer[0]);
  
  public:
    FunkyClouds(CRGB *leds) : Effect(leds), frame(0) {
        multiTimer[0].tact = 70;     //x1
        multiTimer[0].up = WIDTH - 1;
        multiTimer[0].down = 0;
    
        multiTimer[1].tact = 50;     //y1
        multiTimer[1].up = HEIGHT - 1;
        multiTimer[1].down = 0;
    
        multiTimer[2].tact = 3;      //color
        multiTimer[2].up = 255;
        multiTimer[2].down = 0;
    
        multiTimer[3].tact = 76;     //x2  
        multiTimer[3].up = WIDTH - 1;
        multiTimer[3].down = 0;
    
        multiTimer[4].tact = 99;     //y2
        multiTimer[4].up = HEIGHT - 1;
        multiTimer[4].down = 0;
    
        multiTimer[5].tact = 73;    //center spiral x
        multiTimer[5].up = HEIGHT - 4;
        multiTimer[5].down = 0;
    
        multiTimer[6].tact = 145;    //center spiral y
        multiTimer[6].up = HEIGHT - 4;
        multiTimer[6].down = 0;
    
        // set counting directions positive for the beginning
        // and start with random values to keep the start interesting
    
        for (int i = 0; i < timers; i++) {
            multiTimer[i].delta = 1;
            multiTimer[i].count = random(multiTimer[i].up);
        }      
    }
    
    void draw(int rawPot, int rawMic, bool button) {
        // let the oscillators swing
        UpdateTimers();
    
        // the "seed": 3 moving dots
        pixel(multiTimer[0].count, multiTimer[1].count) = CHSV(multiTimer[2].count, 255, 255);
    
        pixel(multiTimer[3].count, multiTimer[4].count) = CHSV(255 - multiTimer[2].count, 255, 255);
    
        // coordinates are the average of 2 oscillators
        pixel((multiTimer[0].count + multiTimer[1].count) / 2, (multiTimer[3].count + multiTimer[4].count) / 2) = CHSV(multiTimer[2].count / 2, 255, 255);
    
        // the balance of the (last) values of the following functions affects the
        // appearence of the effect a lot
    
        // a moving spiral
        SpiralStream(multiTimer[5].count, multiTimer[6].count, 2, 255); // play here
    
        // y wind
        StreamVertical(120);    // and here
    
        // x wind
        StreamHorizontal(110);  // and here
    
        // main spiral
        SpiralStream(15, 15, 15, 150); // and here
    
        // increase the contrast
        DimmAll(250);
    }

    // counts everything with different speeds linear up and down
    // = oscillators following a triangular function
    void UpdateTimers()
    {
        unsigned long now = millis();
        for (int i = 0; i < timers; i++)
        {
            while (now - multiTimer[i].lastMillis >= multiTimer[i].tact)
            {
                multiTimer[i].lastMillis += multiTimer[i].tact;
                multiTimer[i].count = multiTimer[i].count + multiTimer[i].delta;
                if ((multiTimer[i].count == multiTimer[i].up) || (multiTimer[i].count == multiTimer[i].down))
                {
                    multiTimer[i].delta = -multiTimer[i].delta;
                }
            }
        }
    }

    // fade the image buffer arround
    // x, y: center   r: radius   dimm: fade down
    void SpiralStream(int x, int y, int r, byte dimm) {
        for (int d = r; d >= 0; d--) {                // from the outside to the inside
            for (int i = x - d; i <= x + d; i++) {
                pixel(i, y - d) += pixel(i + 1, y - d);   // lowest row to the right
                pixel(i, y - d).nscale8(dimm);
            }
            for (int i = y - d; i <= y + d; i++) {
                pixel(x + d, i) += pixel(x + d, i + 1);   // right colum up
                pixel(x + d, i).nscale8(dimm);
            }
            for (int i = x + d; i >= x - d; i--) {
                pixel(i, y + d) += pixel(i - 1, y + d);   // upper row to the left
                pixel(i, y + d).nscale8(dimm);
            }
            for (int i = y + d; i >= y - d; i--) {
                pixel(x - d, i) += pixel(x - d, i - 1);   // left colum down
                pixel(x - d, i).nscale8(dimm);
            }
        }
    }
    
    // give it a linear tail
    void StreamVertical(byte scale)
    {
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 1; y < HEIGHT; y++) {
                pixel(x, y) += pixel(x, y - 1);
                pixel(x, y).nscale8(scale);
            }
        }
        for (int x = 0; x < WIDTH; x++) {
            pixel(x, 0).nscale8(scale);
        }
    }
    
    // give it a linear tail
    void StreamHorizontal(byte scale)
    {
        for (int x = 1; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                pixel(x, y) += pixel(x - 1, y);
                pixel(x, y).nscale8(scale);
            }
        }
        for (int y = 0; y < HEIGHT; y++) {
            pixel(0, y).nscale8(scale);
        }
    }
    
    // scale the brightness of the screenbuffer down
    void DimmAll(byte value)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i].nscale8(value);
        }
    }
};

#endif
