// Lights up pixels one at a time, so you can see which is next
// Import the needed FastLED library
#include <FastLED.h>

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 5;     // the number of the pushbutton pin

#define NUM_LEDS 93  //This number decides how many of the strip's LEDs the code will use
CRGB leds[NUM_LEDS];
#define DATA_PIN 6
#define BRIGHTNESS  10

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int ledValue = -1;

int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // initiate the LED strip
  
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  FastLED.clear();  // clear all pixel data
  FastLED.show();
}

void loop() {

//  if (ledValue == -1){
//    FastLED.clear();
//  }
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
         ledValue = ledValue + 1;
         if (ledValue > NUM_LEDS - 1) {
            ledValue = -1;
         };
         FastLED.clear();
         //Set and turn on desired LED
         leds[ledValue] = CRGB::Purple;
         FastLED.show();
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
