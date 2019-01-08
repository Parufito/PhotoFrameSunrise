#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 8

//NeoPixel pin
#define DATA_PIN 6

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() { 
  
  sunrise();
  FastLED.show();

}

void sunrise() {
  
  // total sunrise length, in minutes
  static const uint8_t sunriseLength = 5;

  // how often (in seconds) should the heat color increase?
  // for the default of 30 minutes, this should be about every 7 seconds
  // 7 seconds x 256 gradient steps = 1,792 seconds = ~30 minutes
  static const uint8_t interval = (sunriseLength * 60) / 256;

  // current gradient palette color index
  static uint8_t heatIndex = 0; // start out at 0

  // HeatColors_p is a gradient palette built in to FastLED
  // that fades from black to red, orange, yellow, white
  // feel free to use another palette or define your own custom one
  CRGB color = ColorFromPalette(HeatColors_p, heatIndex);

  // fill the entire strip with the current color
  fill_solid(leds, NUM_LEDS, color);

  // slowly increase the heat
  EVERY_N_SECONDS(interval) {
    // stop incrementing at 255, we don't want to overflow back to 0
    if(heatIndex < 255) {
      heatIndex++;
    }
  }
}

