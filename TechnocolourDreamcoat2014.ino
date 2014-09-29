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
//#include "FunkyLine.cpp"
//#include "MiniClouds.cpp"

#define MIC_PIN 23
#define POT_PIN 22
#define ENCODER_PIN0 4
#define ENCODER_PIN1 5
#define ENCODER_BUTTON_PIN 2

#define DATA_PIN 1

#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];

Encoder encoder(ENCODER_PIN0, ENCODER_PIN1);

LayoutTest layoutTest(leds);
ChaseTest chaseTest(leds);

PlainColour plainColourRed(leds, CRGB::Red);
PlainColour plainColourGreen(leds, CRGB::Green);
PlainColour plainColourBlue(leds, CRGB::Blue);
PlainColour plainColourWhite(leds, CRGB::White);

AdvancingPaletteEffect advancingPalette0(leds, HeatColors_p); 
AdvancingPaletteEffect advancingPalette1(leds, RainbowColors_p); 
AdvancingPaletteEffect advancingPalette2(leds, PartyColors_p);
//
FireEffect fire00(leds, 0, HeatColors_p);
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

//FunkyLine funkyLine(leds);
//MiniClouds miniClouds(leds);

Effect* effects0[] = { &scintillate, NULL };

Effect* effects1[] = {
//  &scintillate, NULL
};

Effect* effects2[] = {
//  &fire00, &fire01, &fire02, &fire03, 
//  &fire04, &fire05, &fire06, &fire07,
//  &fire08, &fire09, &fire10, &fire11,
//  NULL
};

Effect* effects3[] = {
//  &perlin, NULL
};

Effect* effects4[] = {
//  &perlin, &scintillate, NULL
};

Effect* effects5[] = {
//  &perlin, &soundSaturation, NULL
};

Effect* effects6[] = {
//  &plasma, NULL
};

Effect* effects7[] = {
//  &plasma, &scintillate, NULL
};

Effect* effects8[] = {
//  &plasma, &soundSaturation, NULL
};

Effect* effects9[] = {
//  &snake, &scintillate, NULL
};

Effect* effects10[] = {
//  &life, &soundSaturation, NULL
};

Effect* effects11[] = {
//  &funkyLine, &soundSaturation, NULL
};

Effect* effects12[] = {
//  &miniClouds, &soundSaturation, NULL
};

EffectGroup group00("Scintillate",         (Effect *[]) {&scintillate, NULL});
EffectGroup group01("Layout Test",         (Effect *[]) {&layoutTest, NULL});
EffectGroup group02("Chase Test",          (Effect *[]) {&chaseTest, NULL});
EffectGroup group03("Power Test (Red)",    (Effect *[]) {&plainColourRed, NULL});
EffectGroup group04("Power Test (Green)",  (Effect *[]) {&plainColourGreen, NULL});
EffectGroup group05("Power Test (Blue)",   (Effect *[]) {&plainColourBlue, NULL});
EffectGroup group06("Power Test (White)",  (Effect *[]) {&plainColourWhite, NULL});

EffectGroup* groups[] = {
    &group00, &group01, &group02, &group03, &group04, &group05, NULL
};

uint8_t encoderDebounce;
uint8_t buttonDebounce;

EffectControls controls;

uint8_t groupsIndex = 0;
uint8_t effectIndex = 0;

Effect** effects;

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

    readControls(&controls);

    effects = groups[groupsIndex]->effects();    
    effectIndex = 0;
    while (effects[effectIndex] != NULL) {
        effects[effectIndex++]->draw(controls);
    }
  //  LEDS.show();
    show_at_max_brightness_for_power();
    
    unsigned long loopStartDelta = millis() - loopStartMillis;
    if (loopStartDelta < 1000 / FRAMES_PER_SECOND) {
  //    LEDS.delay(1000 / FRAMES_PER_SECOND - loopStartDelta);
        delay_at_max_brightness_for_power(1000 / FRAMES_PER_SECOND - loopStartDelta);
    }  
    memset8(leds, 0, NUM_LEDS * sizeof(CRGB));
}

void readControls(EffectControls* controls) {
    controls->buttonVal = false;

    controls->encoderVal = encoder.read();    
    if (controls->encoderDebounce > 0) {
        encoder.write(0);
        controls->encoderDebounce--;
        Serial.print("encoderDebounce = "); Serial.println(encoderDebounce);  
    }
    if (controls->encoderDebounce == 0 && controls->encoderVal != 0) {
        if (digitalRead(ENCODER_BUTTON_PIN) == LOW) {
            // set master brightness
//            Serial.print("Setting master brightness + "); Serial.println(constrain(FastLED.getBrightness() + controls->encoderVal, 0, 255));
            FastLED.setBrightness(constrain(FastLED.getBrightness() + controls->encoderVal * 8, 0, 255));
            controls->encoderDebounce = 0;
        } else {
            // advance effect
//            Serial.print("encoderVal = "); Serial.println(encoderVal);
            controls->encoderVal > 0 ? effectGroupIndex++ : effectGroupIndex--;
            effectGroupIndex = effectGroupIndex == effectGroupCount ? 0 : effectGroupIndex;
            effectGroupIndex = effectGroupIndex == 255 ? effectGroupCount - 1 : effectGroupIndex;
//            Serial.print("effectGroupIndex = "); Serial.println(effectGroupIndex);
            effects = effectGroup[effectGroupIndex];
//            Serial.print("just about to increment encoderDebounce...");
            controls->encoderDebounce = 16;    
        }
        encoder.write(0);
    }
    
    controls->potVal = analogRead(POT_PIN);
    controls->micVal = analogRead(MIC_PIN);
    
    if (buttonDebounce > 0) {
        buttonDebounce--;
    }
    if (buttonDebounce == 0 && digitalRead(ENCODER_BUTTON_PIN) == LOW) {
        controls->buttonVal = true;
        buttonDebounce = 16;
    }
}


