#include <FastLED.h>

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

#define MIC_PIN 23
#define POT_PIN 22
#define ENCODER_PIN0 4
#define ENCODER_PIN1 5
#define ENCODER_BUTTON_PIN 2

#define DATA_PIN 3
#define WIDTH 16
#define HEIGHT 8
#define NUM_LEDS WIDTH * HEIGHT

#define FRAMES_PER_SECOND

CRGB leds[fastLedNumLeds];

Encoder encoder(rotaryEncPin0, rotaryEncPin1);

EffectGroup *effectGroups[] = {
};
uint8_t effectGroupCount = 0;
uint8_t effectGroupIndex = 0;

FrameEffect *effects;

void setup() {
  Serial.begin(57600);
  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
  
  pinMode(rotaryEncButtonPin, INPUT_PULLUP);
  
  effects = effectGroups[0]->effects();
}

void loop() {
  if (encoder.read() != 0) {
    effectGroupIndex += encoder.read();
    effects = effectGroups[effectGroupIndex % effectGroupCount]->effects();
    encoder.write(0);
  }

  potVal = analogRead(potPin);
  micVal = analogRead(micPin);
  
  while (effects[effectIndex] != NULL) {
    effects[effectIndex++]->draw(potVal);
  }
  LEDS.show();
  LEDS.delay(1000 / FRAMES_PER_SECOND);
  memset8(leds, 0, NUM_LEDS * sizeof(CRGB));  
}


