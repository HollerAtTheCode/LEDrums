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
//#define LED_PIN_TOM1 6
//#define LED_PIN_TOM2 7
//#define LED_PIN_TOM3 8
//#define LED_PIN_RACK 9

Adafruit_NeoPixel snareLeds(LED_COUNT_SNARE, LED_PIN_SNARE, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel tom1Leds(LED_COUNT_TOM, LED_PIN_TOM1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel tom2Leds(LED_COUNT_TOM, LED_PIN_TOM2, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel tom3Leds(LED_COUNT_TOM, LED_PIN_TOM3, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel rackLeds(LED_COUNT_RACK, LED_PIN_RACK, NEO_GRB + NEO_KHZ800);

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
  }
  else if (pitch == TOM1 || pitch == TOM1_RIM) {
    Serial.print("TOM1");
  }
  else if (pitch == TOM2 || pitch == TOM2_RIM) {
    Serial.print("TOM2");
  }
  else if (pitch == TOM3 || pitch == TOM3_RIM) {
    Serial.print("TOM3");
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
  //tom1Leds.begin();
  //tom2Leds.begin();
  //tom3Leds.begin();
  //rackLeds.begin();
  
  pinMode (LED, OUTPUT);
  MIDI.begin(10);
  MIDI.setHandleNoteOn(MyHandleNoteOn);
}

void loop() { // Main loop
  MIDI.read(); // Continually check what Midi Commands have been received.
}
