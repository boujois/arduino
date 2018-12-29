#include <FastLED.h>
#define NUM_LEDS 6
#define DATA_PIN    9
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define BRIGHTNESS 40 
int loopNumber = 0;

CRGBArray<NUM_LEDS> leds;
 
int ch1; // Here's where we'll keep our channel values
int ch2;
int ch3;

void setup() {

  pinMode(3, INPUT); // Set our input pins as such
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  Serial.begin(9600); // Pour a bowl of Serial

  pinMode(LED_BUILTIN, OUTPUT);

  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  leds[0] = CRGB::Red;
  leds[5] = CRGB::Green;
}

void loop() {

  ch1 = pulseIn(3, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(4, HIGH, 25000); // each channel
  ch3 = pulseIn(5, HIGH, 25000);

  Serial.print("Channel 1:"); // Print the value of 
  Serial.println(ch1);        // each channel
  if(ch1>1800){
    Serial.println("Switch: Off");
    digitalWrite(LED_BUILTIN, LOW);
  }
  if(ch1<1400){
    Serial.println("Switch: On");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if(ch1>=1400 && ch1<=1800){
    Serial.println("Switch: Middle");
    digitalWrite(LED_BUILTIN, LOW);
  }

//  Serial.print("Channel 2:");
//  Serial.println(ch2);
//
//  Serial.print("Channel 3:");
//  Serial.println(ch3);

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

  if(ch1>1400){
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

  if(ch1>1800){
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
  }
  
}
