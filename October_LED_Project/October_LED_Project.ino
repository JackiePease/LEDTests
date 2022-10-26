#include "FastLED.h"

#define NUM_LEDS 650

CRGB leds[NUM_LEDS];
CHSV ledsSource[NUM_LEDS];
CHSV ledsTarget[NUM_LEDS];

bool glowUpEclairs[NUM_LEDS];

#include "spiral.h"

#define BRIGHTNESS 200

uint8_t ledHue = 0;

uint8_t OREO_LENGTH = 8;
uint8_t HARIBO_LENGTH = 4;
uint8_t WISPA_LENGTH = 10;
uint8_t ECLAIR_LENGTH = 15;

uint8_t NOTHING_HUE = 0;
uint8_t HARIBO_HUE = 235;
uint8_t OREO_HUE = 20;
uint8_t WISPA_HUE = 127;
uint8_t ECLAIR_HUE = 0;

uint8_t NOTHING_SATURATION = 0;
uint8_t HARIBO_SATURATION = 180;
uint8_t OREO_SATURATION = 180;
uint8_t WISPA_SATURATION = 180;
uint8_t ECLAIR_SATURATION = 0;

uint8_t NOTHING_VALUE = 0;
uint8_t HARIBO_VALUE = 200;
uint8_t OREO_VALUE = 200;
uint8_t WISPA_VALUE = 200;
uint8_t ECLAIR_VALUE = 100;

int iDelaySet = 4;
int iBlendSteps = 6;

// Define the spirals
spiral gSpirals[13];

void setup() {
  randomSeed(analogRead(4));
  FastLED.addLeds<NEOPIXEL, 9>(leds, 0, 150);
  FastLED.addLeds<NEOPIXEL, 10>(leds, 150, 100);
  FastLED.addLeds<NEOPIXEL, 11>(leds, 250, 150);
  FastLED.addLeds<NEOPIXEL, 12>(leds, 400, 150);
  FastLED.addLeds<NEOPIXEL, 13>(leds, 550, 100);

  FastLED.clear();  // clear all pixel data
  FastLED.show();
  // Set up the spirals
  gSpirals[0].setup(0, 50);
  gSpirals[1].setup(50, 50);
  gSpirals[2].setup(100, 50);
  gSpirals[3].setup(150, 50);
  gSpirals[4].setup(200, 50);  
  gSpirals[5].setup(250, 50);  
  gSpirals[6].setup(300, 50);  
  gSpirals[7].setup(350, 50);
  gSpirals[8].setup(400, 50);
  gSpirals[9].setup(450, 50);
  gSpirals[10].setup(500, 50);
  gSpirals[11].setup(550, 50);
  gSpirals[12].setup(600, 50);
  
  for(int i = 0; i < NUM_LEDS; i++) {
      ledsSource[i] = CHSV(0, 0, 0);
      ledsTarget[i] = CHSV(0, 0, 0);
  }
}

void loop() {
  // Animate the sprials
  for (int i = 0; i < 13; i++) { 
    gSpirals[i].advance();    
  }
  
  for (int j = 0; j < iBlendSteps; j++){
    int delta = round(float(j + 1) / float(iBlendSteps + 1) * 255);
    for (int i = 0; i < NUM_LEDS; i++) {
      if (glowUpEclairs[i]) { 
        leds[i] = CHSV(ECLAIR_HUE, ECLAIR_SATURATION, ECLAIR_VALUE);
      } else {
        if (ledsTarget[i] == CHSV(0, 0, 0)) {
          leds[i] = CHSV(0,0,0);
        } else {
          leds[i] = blend( ledsSource[i], ledsTarget[i], delta, SHORTEST_HUES );
        }
      }
    }
  }

  FastLED.show();

  for (int i = 0; i < NUM_LEDS; i++) {
    ledsSource[i] = ledsTarget[i];
    glowUpEclairs[i] = 0;
  }

  delay(iDelaySet);

}
