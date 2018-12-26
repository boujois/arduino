#include <FastLED.h>
#define NUM_LEDS 6
#define DATA_PIN    3
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define BRIGHTNESS 40 
int loopNumber = 0;

CRGBArray<NUM_LEDS> leds;

void setup() {
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  leds[0] = CRGB::Red;
  leds[5] = CRGB::Green;
}

void loop(){ 
    loopNumber = loopNumber + 1;

    handleWhiteStrobe();
    handleRedStrobe();

    delay(100);
    FastLED.show();
    
    if(loopNumber > 12){
      loopNumber = 0;
    }
}

void handleWhiteStrobe(){
  if(loopNumber==1 || loopNumber==4 || loopNumber==5){
    leds[1] = CRGB::White;
    leds[4] = CRGB::White;
  }
  else{
    leds[1] = CRGB::Black;
    leds[4] = CRGB::Black;    
  }
}

void handleRedStrobe(){
  if(loopNumber == 6 || loopNumber == 7){
    leds[2] = CRGB::Red;
    leds[3] = CRGB::Red;
  }
  else{
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
  }
}
