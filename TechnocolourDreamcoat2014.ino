#include <FastLED.h>

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

#include "Effect.cpp"
#include "EffectGroup.cpp"
#include "AdvancingPaletteEffect.cpp"

#define MIC_PIN 23
#define POT_PIN 22
#define ENCODER_PIN0 4
#define ENCODER_PIN1 5
#define ENCODER_BUTTON_PIN 2

#define DATA_PIN 3
#define WIDTH 16
#define HEIGHT 8
#define NUM_LEDS WIDTH * HEIGHT

#define FRAMES_PER_SECOND 60

CRGB leds[NUM_LEDS];

Encoder encoder(ENCODER_PIN0, ENCODER_PIN1);

AdvancingPaletteEffect advancingPalette(leds, WIDTH, HEIGHT, HeatColors_p); 

Effect* effects0[] = {
  &advancingPalette, &advancingPalette, &advancingPalette, NULL
};

Effect* effects1[] = {
  &advancingPalette, &advancingPalette, &advancingPalette, NULL
};

Effect* effects2[] = {
  &advancingPalette, &advancingPalette, &advancingPalette, NULL
};

Effect** effectGroups[] = {
  effects0, effects1, effects2
};

Effect **effects = effectGroups[0];

uint8_t effectGroupCount = 3;
uint8_t effectGroupIndex = 0;

int micVal;
int potVal;

uint8_t effectIndex;

void setup() {
  Serial.begin(57600);
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
  
  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (encoder.read() != 0) {
    effectGroupIndex += encoder.read();
    effects = effectGroups[effectGroupIndex % effectGroupCount];
    encoder.write(0);
  }

  potVal = analogRead(MIC_PIN);
  micVal = analogRead(POT_PIN);
  
  effectIndex = 0;
  while (effects[effectIndex] != NULL) {
    effects[effectIndex++]->draw(micVal);
  }
  LEDS.show();
  LEDS.delay(1000 / FRAMES_PER_SECOND);
  memset8(leds, 0, NUM_LEDS * sizeof(CRGB));  
}


