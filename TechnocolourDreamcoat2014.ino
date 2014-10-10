#include <FastLED.h>

#include "Effect.cpp"

#include "LayoutTest.cpp"
#include "ChaseTest.cpp"
#include "PowerTest.cpp"
#include "PlainColour.cpp"
//#include "AdvancingPaletteEffect.cpp"
//#include "FireEffect.cpp"
#include "Life.cpp"
#include "Plasma.cpp"
#include "Scintillate.cpp"
#include "Perlin.cpp"
#include "Snake.cpp"
//#include "SoundSaturation.cpp"
//#include "RotatingCube.cpp"
//#include "Mandelbrot.cpp"
//#include "RandomPainter.cpp"
//#include "FunkyLine.cpp"
//#include "MiniClouds.cpp"

#define DATA_PIN 1
#define PROG_UP_PIN 2
#define PROG_DOWN_PIN 3
#define BRIGHTNESS_PIN 21 // A7

#define FRAMES_PER_SECOND 60
#define DEBOUNCE_COUNT 16

CRGB leds[NUM_LEDS];

LayoutTest layoutTest(leds);
ChaseTest chaseTest(leds);

PlainColour plainColourRed(leds, "Power Test (Red)", CRGB::Red);
PlainColour plainColourGreen(leds, "Power Test (Green)", CRGB::Green);
PlainColour plainColourBlue(leds, "Power Test (Blue)", CRGB::Blue);
PlainColour plainColourWhite(leds, "Power Test (White)", CRGB::White);

//AdvancingPaletteEffect advancingPalette0(leds, HeatColors_p); 
//AdvancingPaletteEffect advancingPalette1(leds, RainbowColors_p); 
//AdvancingPaletteEffect advancingPalette2(leds, PartyColors_p);
//
//FireEffect fire00(leds, 0, HeatColors_p);
//FireEffect fire01(leds, 1, HeatColors_p);
//FireEffect fire02(leds, 2, HeatColors_p);
//FireEffect fire03(leds, 3, HeatColors_p);
//FireEffect fire04(leds, 4, HeatColors_p);
//FireEffect fire05(leds, 5, HeatColors_p);
//FireEffect fire06(leds, 6, HeatColors_p);
//FireEffect fire07(leds, 7, HeatColors_p);
//FireEffect fire08(leds, 8, HeatColors_p);
//FireEffect fire09(leds, 9, HeatColors_p);
//FireEffect fire10(leds, 10, HeatColors_p);
//FireEffect fire11(leds, 11, HeatColors_p);
//
//Life life(leds);
Plasma plasma(leds);
Scintillate scintillate(leds);
Perlin perlin(leds);
Snake snake(leds);
//SoundSaturation soundSaturation(leds);
//
//RotatingCube cube(leds);
//Mandelbrot mandelbrot(leds);
//RandomPainter randomPainter(leds);
//
//FunkyLine funkyLine(leds);
//MiniClouds miniClouds(leds);


Effect* effects[] = {
    &layoutTest, &chaseTest, &plainColourRed, &plainColourGreen, &plainColourBlue, &plainColourWhite, &scintillate, &plasma, &perlin, &snake,
//    &life,
    NULL
};

EffectControls controls;

uint8_t effectIndex = 0;
uint8_t effectCount = 0;

void setup() {
  Serial.begin(115200);
 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  
  pinMode(PROG_UP_PIN, INPUT_PULLUP);
  pinMode(PROG_DOWN_PIN, INPUT_PULLUP);  
  pinMode(13, OUTPUT);

  set_max_power_indicator_LED(13);
  set_max_power_in_milliwatts(80000);
  
  while (effects[effectIndex++] != NULL) {
      effectCount++;
  }
  effectIndex = 0;

  delay(2000);  
}

void loop() {
    unsigned long loopStartMillis = millis();
//    Serial.print("loopStartMillis = "); Serial.println(loopStartMillis);
//    Serial.print("effectCount = "); Serial.println(effectCount);

    readControls(&controls);
//    Serial.print("controls.progUp = "); Serial.print(controls.progUp); Serial.print(", controls.progDown = "); Serial.print(controls.progDown); Serial.print(", controls.brightness = "); Serial.println(controls.brightness);
    if (controls.progUp && controls.progDown) {
        // special mode?
    } else if (controls.progUp) {
        effectIndex = effectIndex == effectCount - 1 ? 0 : effectIndex + 1;
    } else if (controls.progDown) {
        effectIndex = effectIndex == 0 ? effectCount - 1 : effectIndex - 1;
    }
    Serial.print("effectIndex: "); Serial.println(effectIndex);    
    Effect *effect = effects[effectIndex];
    
    FastLED.setBrightness(controls.brightness);
    
//    Serial.print("effect.name(): "); Serial.println(effect->name());
    
    effect->draw(controls);

    LEDS.show();
//    show_at_max_brightness_for_power();
    
    unsigned long loopStartDelta = millis() - loopStartMillis;
    if (loopStartDelta < 1000 / FRAMES_PER_SECOND) {
        LEDS.delay(1000 / FRAMES_PER_SECOND - loopStartDelta);
//        delay_at_max_brightness_for_power(1000 / FRAMES_PER_SECOND - loopStartDelta);
    }  
    memset8(leds, 0, NUM_LEDS * sizeof(CRGB));  
}

void readControls(EffectControls* controls) {
    if (controls->progUpDebounce == 0 && digitalRead(PROG_UP_PIN) == LOW) {
        Serial.println("progUpDebounce");
        controls->progUpDebounce = DEBOUNCE_COUNT;      
        controls->progUp = true;
    } else if (controls->progUpDebounce > 0) {
        controls->progUpDebounce--;
        controls->progUp = false;
    }
    
    if (controls->progDownDebounce == 0 && digitalRead(PROG_DOWN_PIN) == LOW) {
        Serial.println("progDownDebounce");      
        controls->progDownDebounce = DEBOUNCE_COUNT;
        controls->progDown = true;
    } else if (controls->progDownDebounce > 0) {
        controls->progDownDebounce--;
        controls->progDown = false;        
    }
    
    controls->brightness =  map(analogRead(BRIGHTNESS_PIN), 0, 1023, 0, 255);
}


