#ifndef LifeEffect_h
#define LifeEffect_h

#import "Effect.cpp"

#define DELTA_LEN (WIDTH * HEIGHT / 16) // This is probably going to bite me for non-even NUM_LEDS / 16, need a +1 here?

class LifeEffect : public Effect {
    
private:
    
    uint8_t density;
    uint8_t hue;
    uint16_t delta[DELTA_LEN];
    
public:
    
    LifeEffect(CRGB *leds, int density): Effect(leds), density(density) {
        uint8_t hue = random(255);
        for (int i = 0; i < NUM_LEDS; i++) {
            if (random(255) < density) {
                leds[i] = CHSV(hue, 255, 255);
            }
        }
    }
    
    void draw(uint8_t micVal) {
        delay(100);
        Serial.print("draw, with DELTA_LEN = "); Serial.println(DELTA_LEN);
      
        for (int x = 0; x < WIDTH; x++) {
             for (int y = 0; y < HEIGHT; y++) {
                 int neighbours = numNeighbours(x, y);
                 if (pixel(x, y)) {
                    if (neighbours < 2 || neighbours > 3) {
                        setChanged(x, y);
                    }
                } else {
                    if (neighbours == 3) {
                        setChanged(x, y);
                    }
                }
            }
        }
        updateWithChanges(hue++);
        for (int i = 0; i < DELTA_LEN; i++) {
            delta[i] = 0;
        }
    }
    
    /*
    x - 1, y + 1|x = x, y + 1|x + 1, y + 1
    x - 1, y = y|      x     |x + 1, y = y
    x - 1, y - 1|x = x, y - 1|x + 1, y - 1
    */
    
    int numNeighbours(int x, int y) {
        int numNeighbours = 0;
        numNeighbours += alive(x - 1, y + 1) ? 1 : 0;
        numNeighbours += alive(x, y + 1) ? 1 : 0;
        numNeighbours += alive(x + 1, y + 1) ? 1 : 0;
        numNeighbours += alive(x - 1, y) ? 1 : 0;
        numNeighbours += alive(x + 1, y) ? 1 : 0;
        numNeighbours += alive(x - 1, y - 1) ? 1 : 0;
        numNeighbours += alive(x, y - 1) ? 1 : 0;
        numNeighbours += alive(x + 1, y - 1) ? 1 : 0;
        return numNeighbours;
    }
    
    bool alive(int x, int y) {
        return inXRange(x) && inYRange(y) && pixel(x, y);
    }
    
    // xxxx xxxx xxxx xxxx  xxxx xxxx xxxx xxxx
    // xxxx xxxx xxxx xxxx  xxxx xxxx xxxx xxxx
    
    void setChanged(int x, int y) {
        delta[deltaIndex(x, y)] |= 1 << (x < 16 ? x : x - 16);
    }
    
    void updateWithChanges(uint8_t time) {
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                if (delta[deltaIndex(x, y)] & (1 << (x < 16 ? x : x - 16))) {
                    if (pixel(x, y)) {
                        pixel(x, y) = CRGB::Black;
                    } else {
                        pixel(x, y) = CHSV(time, 255, 255);
                    }
                }
            }
        }
        // add some random pixels so we don't decay completely
        for (int i = 0; i < random(5); i++) {  
            leds[random(WIDTH * HEIGHT)] = CHSV(time, 255, 255);
        }
    }
    
    int deltaIndex(int x, int y) {
        return y + (x < 16 ? 0 : 1);
    }
    
//        Serial.println("draw()");
//         Serial.print("deltaIndex("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.print(") = "); Serial.println(deltaIndex);

};

#endif
