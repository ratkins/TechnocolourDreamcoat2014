#include <FastLED.h>

//#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

#include "Effect.cpp"
#include "EffectGroup.cpp"

#include "LayoutTest.cpp"
#include "ChaseTest.cpp"
#include "PlainColour.cpp"
#include "AdvancingPaletteEffect.cpp"
#include "FireEffect.cpp"
#include "LifeEffect.cpp"
#include "Plasma.cpp"

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
FireEffect fire12(leds, 12, HeatColors_p);
FireEffect fire13(leds, 13, HeatColors_p);
FireEffect fire14(leds, 14, HeatColors_p);
FireEffect fire15(leds, 15, HeatColors_p);

LifeEffect life(leds, 200);

Plasma plasma0(leds, RainbowColors_p);
Plasma plasma1(leds, RainbowStripeColors_p);
Plasma plasma2(leds, PartyColors_p);
Plasma plasma3(leds, OceanColors_p);

Effect* effects0[] = {
//  &layoutTest, NULL
//  &chaseTest, NULL
//  &plainColourWhite, NULL
  &plasma1, NULL
//  &life, NULL
};

Effect* effects1[] = {
//  &fire00, &fire01, &fire02, &fire03, &fire04, &fire05, &fire06, &fire07,
//  &fire08, &fire09, &fire10, &fire11, &fire12, &fire13, &fire14, &fire15, NULL  
  &plasma2, NULL
};

Effect* effects2[] = {
//  &life, NULL
//  &plainColourRed, NULL
  &plasma3, NULL
};

Effect** effectGroup[] = {
  effects0, effects1, effects2
};

Effect **effects = effectGroup[0];

uint8_t effectGroupCount = 3;
uint8_t effectGroupIndex = 0;

long encoderVal;
uint8_t encoderDebounce;

int micVal;
int potVal;

uint8_t effectIndex = 0;

void setup() {
  Serial.begin(57600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(128);
  
  delay(2000);
  
  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  unsigned long loopStartMillis = millis();
//  Serial.print("loopStartMillis = "); Serial.println(loopStartMillis);        
  encoderVal = encoder.read();
  if (encoderDebounce > 0) {
      encoder.write(0);
      encoderDebounce--;
//      Serial.print("encoderDebounce = "); Serial.println(encoderDebounce);  
  }
  if (encoderDebounce == 0 && encoderVal != 0) {
//    Serial.print("encoderVal = "); Serial.println(encoderVal);
    effectGroupIndex += encoderVal;
//    Serial.print("effectGroupIndex = "); Serial.print(effectGroupIndex); Serial.print(", aka "); Serial.println(effectGroupIndex % effectGroupCount);
    effects = effectGroup[effectGroupIndex % effectGroupCount];
    encoder.write(0);
//    Serial.print("just about to increment encoderDebounce...");
    encoderDebounce = 8;
//    Serial.print(" encoderDebounce = "); Serial.println(encoderDebounce);      
  }

  potVal = analogRead(MIC_PIN);
  micVal = analogRead(POT_PIN);
  
  effectIndex = 0;
  while (effects[effectIndex] != NULL) {
    effects[effectIndex++]->draw(micVal);
  }
  LEDS.show();
  
  unsigned long loopStartDelta = millis() - loopStartMillis;
  if (loopStartDelta < 1000 / FRAMES_PER_SECOND) {
    LEDS.delay(1000 / FRAMES_PER_SECOND - loopStartDelta);
  }  
  memset8(leds, 0, NUM_LEDS * sizeof(CRGB));
}


