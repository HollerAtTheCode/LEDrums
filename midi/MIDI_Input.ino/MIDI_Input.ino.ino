#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <MIDI.h>  // Add Midi Library
#include <SoftwareSerial.h>

#define LED 13    // Arduino Board LED is on Pin 13

// LEDs
#define LED_COUNT_TOM 18
#define LED_COUNT_SNARE 28
#define LED_COUNT_RACK 20

#define LED_PIN_SNARE 5
#define LED_PIN_TOM1 6
#define LED_PIN_TOM2 7
#define LED_PIN_TOM3 8
#define LED_PIN_RACK 9

Adafruit_NeoPixel snareLeds = Adafruit_NeoPixel(LED_COUNT_SNARE, LED_PIN_SNARE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel tom1Leds = Adafruit_NeoPixel(LED_COUNT_TOM, LED_PIN_TOM1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel tom2Leds = Adafruit_NeoPixel(LED_COUNT_TOM, LED_PIN_TOM2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel tom3Leds = Adafruit_NeoPixel(LED_COUNT_TOM, LED_PIN_TOM3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rackLeds = Adafruit_NeoPixel(LED_COUNT_RACK, LED_PIN_RACK, NEO_GRB + NEO_KHZ800);

// Drum Mappings
#define HIHAT_TOP 46
#define HIHAT_TOP_CLOSED 42
#define HIHAT_RIM 26
#define HIHAT_RIM_CLOSED 22
#define HIHAT_PEDAL 44
#define CRASH_TOP 49
#define CRASH_RIM 55
#define RIDE_TOP 51
#define RIDE_RIM 59
#define RIDE_BELL 53
#define SPLASH_TOP 57
#define SPLASH_RIM 52
#define KICK 36
#define SNARE 38
#define SNARE_RIM 37
#define SNARE_RIM2 40
#define TOM1 48
#define TOM1_RIM 50
#define TOM2 45
#define TOM2_RIM 47
#define TOM3 43
#define TOM3_RIM 58
#define TOM4 41
#define TOM4_RIM 39

SoftwareSerial midiserial(4, 3); // RX, TX
MIDI_CREATE_INSTANCE(SoftwareSerial,midiserial,MIDI);

// Below is my function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  digitalWrite(LED,HIGH);  //Turn LED on
  if (velocity == 0) {//A NOTE ON message with a velocity = Zero is actualy a NOTE OFF
    digitalWrite(LED,LOW);//Turn LED off
  }
  if (pitch == SNARE || pitch == SNARE_RIM || pitch == SNARE_RIM2) {
    Serial.print("Snare");
    snareLeds.setBrightness(velocity);
    snareLeds.show();
    delay(100);
    snareLeds.setBrightness(5);
    snareLeds.show();
  }
  else if (pitch == TOM1 || pitch == TOM1_RIM) {
    Serial.print("TOM1");
    tom1Leds.setBrightness(velocity);
    tom1Leds.show();
    delay(100);
    tom1Leds.setBrightness(5);
    tom1Leds.show();
  }
  else if (pitch == TOM2 || pitch == TOM2_RIM) {
    Serial.print("TOM2");
    tom2Leds.setBrightness(velocity);
    tom2Leds.show();
    delay(100);
    tom2Leds.setBrightness(5);
    tom2Leds.show();
  }
  else if (pitch == TOM3 || pitch == TOM3_RIM) {
    Serial.print("TOM3");
    tom3Leds.setBrightness(velocity);
    tom3Leds.show();
    delay(100);
    tom3Leds.setBrightness(5);
    tom3Leds.show();
  }
  else if (pitch == CRASH_TOP || pitch == CRASH_RIM) {
    Serial.print("Crash");
  }
  else if (pitch == SPLASH_TOP || pitch == SPLASH_RIM) {
    Serial.print("Splash");
  }
  else if (pitch == RIDE_TOP || pitch == RIDE_RIM || pitch == RIDE_BELL) {
    Serial.print("Ride");  
  }
  else if (pitch == KICK) {
    Serial.print("Kick");
  }
}

void setup() {
  midiserial.begin(31250);
  Serial.begin(9600);

  snareLeds.begin();
  snareLeds.setBrightness(5);
  colorWipe(&snareLeds, snareLeds.Color(166, 32, 106), 50, LED_COUNT_SNARE);
  snareLeds.show();
  
  tom1Leds.begin();
  tom1Leds.setBrightness(5);
  colorWipe(&tom1Leds, tom1Leds.Color(241, 106, 67), 50, LED_COUNT_TOM);
  tom1Leds.show();

  tom2Leds.begin();
  tom2Leds.setBrightness(5);
  colorWipe(&tom2Leds, tom2Leds.Color(247, 217, 105), 50, LED_COUNT_TOM);
  tom2Leds.show();
  
  tom3Leds.begin();
  tom3Leds.setBrightness(5);
  colorWipe(&tom3Leds, tom3Leds.Color(47, 147, 149), 50, LED_COUNT_TOM);
  tom3Leds.show();
  
  //rackLeds.begin();
  pinMode (LED, OUTPUT);
  MIDI.begin(10);
  MIDI.setHandleNoteOn(MyHandleNoteOn);
}

void colorWipe(Adafruit_NeoPixel *ledStrip, uint32_t color, int wait, int ledCount) {
  for(int i=0; i<ledCount; i++) { // For each pixel in strip...
    ledStrip->setPixelColor(i, color);         //  Set pixel's color (in RAM)
    ledStrip->show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void loop() {
  // Main loop
  MIDI.read(); // Continually check what Midi Commands have been received.
}
