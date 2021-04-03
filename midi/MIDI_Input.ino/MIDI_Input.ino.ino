#include <MIDI.h>  // Add Midi Library
#include <SoftwareSerial.h>

#define LED 13    // Arduino Board LED is on Pin 13

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
  Serial.print("Type: ");
      Serial.println(channel);
      Serial.print("Note: ");
      Serial.println(pitch);
      Serial.print("Vel: ");
      Serial.println(velocity);   
}

void setup() {
  midiserial.begin(31250);
  Serial.begin(9600);
  
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  MIDI.begin(10); // Initialize the Midi Library.
// OMNI sets it to listen to all channels.. MIDI.begin(2) would set it
// to respond to channel 2 notes only.
  MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function I want called when a Note ON command
  // is received. in this case it's "MyHandleNoteOn".
}

void loop() { // Main loop
  MIDI.read(); // Continually check what Midi Commands have been received.
}
