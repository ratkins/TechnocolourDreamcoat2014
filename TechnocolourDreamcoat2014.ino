#include <FastLED.h>

//#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

#include "Effect.cpp"
#include "EffectGroup.cpp"

#include "LayoutTest.cpp"
#include "ChaseTest.cpp"
#include "PowerTest.cpp"
#include "PlainColour.cpp"
#include "AdvancingPaletteEffect.cpp"
#include "FireEffect.cpp"
#include "Life.cpp"
#include "Plasma.cpp"
#include "Scintillate.cpp"
#include "Perlin.cpp"
#include "Snake.cpp"
#include "SoundSaturation.cpp"
//#include "RotatingCube.cpp"
//#include "Mandelbrot.cpp"
//#include "RandomPainter.cpp"
#include "FunkyClouds.cpp"

#define MIC_PIN 23
#define POT_PIN 22
#define ENCODER_PIN0 4
#define ENCODER_PIN1 5
#define ENCODER_BUTTON_PIN 2

#define DATA_PIN 3

#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];

Encoder encoder(ENCODER_PIN0, ENCODER_PIN1);

LayoutTest layoutTest(leds);
ChaseTest chaseTest(leds);
PowerTest powerTestRed(leds, CRGB::Red);
PowerTest powerTestGreen(leds, CRGB::Green);
PowerTest powerTestBlue(leds, CRGB::Blue);

PlainColour plainColourRed(leds, CRGB::Red);
PlainColour plainColourGreen(leds, CRGB::Green);
PlainColour plainColourBlue(leds, CRGB::Blue);
PlainColour plainColourWhite(leds, CRGB::White);

AdvancingPaletteEffect advancingPalette0(leds, HeatColors_p); 
AdvancingPaletteEffect advancingPalette1(leds, RainbowColors_p); 
AdvancingPaletteEffect advancingPalette2(leds, PartyColors_p);

FireEffect fire00(leds, 0, HeatColors_p);
FireEffect fire01(leds, 1, HeatColors_p);
FireEffect fire02(leds, 2, HeatColors_p);
FireEffect fire03(leds, 3, HeatColors_p);
FireEffect fire04(leds, 4, HeatColors_p);
FireEffect fire05(leds, 5, HeatColors_p);
FireEffect fire06(leds, 6, HeatColors_p);
FireEffect fire07(leds, 7, HeatColors_p);
FireEffect fire08(leds, 8, HeatColors_p);
FireEffect fire09(leds, 9, HeatColors_p);
FireEffect fire10(leds, 10, HeatColors_p);
FireEffect fire11(leds, 11, HeatColors_p);

Life life(leds);

Plasma plasma(leds);

Scintillate scintillate(leds);

Perlin perlin(leds);

Snake snake(leds);

SoundSaturation soundSaturation(leds);

//RotatingCube cube(leds);
//
//Mandelbrot mandelbrot(leds);

//RandomPainter randomPainter(leds);

FunkyClouds funkyClouds(leds);

Effect* effects0[] = {
//  &snake, &soundSaturation, NULL
//  &layoutTest, NULL
//  &chaseTest, NULL
//  &plainColourWhite, NULL
//  &mandelbrot, NULL
//  &randomPainter, NULL
//  &funkyClouds, NULL
};

Effect* effects1[] = {
  &scintillate, NULL
};

Effect* effects2[] = {
  &fire00, &fire01, &fire02, &fire03, 
  &fire04, &fire05, &fire06, &fire07,
  &fire08, &fire09, &fire10, &fire11,
  NULL
};

Effect* effects3[] = {
  &perlin, NULL
};

Effect* effects4[] = {
  &perlin, &scintillate, NULL
};

Effect* effects5[] = {
  &perlin, &soundSaturation, NULL
};

Effect* effects6[] = {
  &plasma, NULL
};

Effect* effects7[] = {
  &plasma, &scintillate, NULL
};

Effect* effects8[] = {
  &plasma, &soundSaturation, NULL
};

Effect* effects9[] = {
  &snake, &scintillate, NULL
};

Effect* effects10[] = {
  &life, &soundSaturation, NULL
};

Effect* effects11[] = {
  &funkyClouds, &soundSaturation, NULL
};

uint8_t effectGroupCount = 12;
Effect** effectGroup[] = {
  effects0, effects1, effects2, effects3, effects4, effects5, effects6, effects7, effects8, effects9, effects10, effects12
};

uint8_t effectGroupIndex = 0;
Effect **effects = effectGroup[0];

long encoderVal;
uint8_t encoderDebounce;

int micVal;
int potVal;

bool buttonVal;
uint8_t buttonDebounce;

uint8_t effectIndex = 0;

void setup() {
//  Serial.begin(57600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  
  pinMode(13, OUTPUT);
  set_max_power_indicator_LED(13);
  set_max_power_in_milliwatts(80000);
  
  delay(2000);
  
  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    unsigned long loopStartMillis = millis();
//    Serial.print("loopStartMillis = "); Serial.println(loopStartMillis);        
    encoderVal = encoder.read();
    if (encoderDebounce > 0) {
        encoder.write(0);
        encoderDebounce--;
//        Serial.print("encoderDebounce = "); Serial.println(encoderDebounce);  
    }
    if (encoderDebounce == 0 && encoderVal != 0) {
        if (digitalRead(ENCODER_BUTTON_PIN) == LOW) {
            // set master brightness
//            Serial.print("Setting master brightness + "); Serial.println(constrain(FastLED.getBrightness() + encoderVal, 0, 255));
            FastLED.setBrightness(constrain(FastLED.getBrightness() + encoderVal * 8, 0, 255));
            encoderDebounce = 0;
        } else {
            // advance effect
//            Serial.print("encoderVal = "); Serial.println(encoderVal);
            effectGroupIndex += encoderVal > 0 ? 1 : -1;
//            Serial.print("effectGroupIndex = "); Serial.print(effectGroupIndex); Serial.print(", aka "); Serial.println(effectGroupIndex % effectGroupCount);
            effects = effectGroup[effectGroupIndex % effectGroupCount];
//            Serial.print("just about to increment encoderDebounce...");
            encoderDebounce = 16;    
        }
        encoder.write(0);
    }
    
    potVal = analogRead(POT_PIN);
    micVal = analogRead(MIC_PIN);
    
    if (buttonDebounce > 0) {
        buttonDebounce--;
    }
    if (buttonDebounce == 0 && digitalRead(ENCODER_BUTTON_PIN) == LOW) {
        buttonVal = true;
        buttonDebounce = 16;
    }
//    Serial.print("Rendering effects with button = "); Serial.println(buttonVal);
    effectIndex = 0;
    while (effects[effectIndex] != NULL) {
        effects[effectIndex++]->draw(potVal, micVal, buttonVal);
    }
    buttonVal = false;
  //  LEDS.show();
    show_at_max_brightness_for_power();
    
    unsigned long loopStartDelta = millis() - loopStartMillis;
    if (loopStartDelta < 1000 / FRAMES_PER_SECOND) {
  //    LEDS.delay(1000 / FRAMES_PER_SECOND - loopStartDelta);
        delay_at_max_brightness_for_power(1000 / FRAMES_PER_SECOND - loopStartDelta);
    }  
    memset8(leds, 0, NUM_LEDS * sizeof(CRGB));
}


