/*
#include <IRremote.h>
#define MAX_TIME 150 // max ms between codes
#define LED_PIN 3
long lastPressTime = 0;
int state = LOW;

int IR_RECEIVE_PIN = 11; // Receive on pin 11

void setup()
{
  pinMode(LED_PIN, OUTPUT);  // Status on pin 3 LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition
}

void loop() {
  if (IrReceiver.decode()) {
    if (1) {  // Can check for a specific button here e.g. if (IrReceiver.decodedIRData.command == 0x11) {
      if (state == LOW) { 
        state = HIGH;  // Button pressed, so set state to HIGH
        digitalWrite(LED_PIN, HIGH);
      }
      lastPressTime = millis();
    }
    IrReceiver.resume(); // Receive the next value
  }
  if (state == HIGH && millis() - lastPressTime > MAX_TIME) {
    state = LOW; // Haven't heard from the button for a while, so not pressed
    digitalWrite(LED_PIN, LOW);
  }
}
*/