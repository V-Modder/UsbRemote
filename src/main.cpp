#include <Arduino.h>
#include <HID-Project.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
#define MAX_TIME 120
#define IR_REMOTE_ADDRESS 0xF902

#define IR_LEFT 0x03
#define IR_RIGHT 0x02
#define IR_UP 0x00
#define IR_DOWN 0x01
#define IR_OK 0x1F
#define IR_MENU 0x04
#define IR_BACK 0x1C
#define IR_HOME 0x65
#define IR_PLAY 0x55
#define IR_PASUE 0x07
#define IR_STOP 0x54
#define IR_NEXT 0x4C
#define IR_PREVIOUS 0x50
#define IR_VOLUME_UP 0x4E
#define IR_VOLUME_DOWN 0x4F
#define IR_VOLUME_MUTE 0x0C
#define IR_SHUTDOWN 0x0A

unsigned int LAST_KEY;
unsigned long LAST_PRESS_TIME = 0;
int STATE = LOW;

void setup() {
  Serial.begin(115200);
  Serial.println("UsbRemote starting...");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  IrReceiver.begin(IR_RECEIVE_PIN);

  NKROKeyboard.begin();
  Consumer.begin();
  System.begin();

  Serial.println("UsbRemote starting...");
  digitalWrite(LED_BUILTIN, LOW);
}

void convertIrCodeToKeyboardKey(unsigned int code) {
  if(code == IR_LEFT) {
    NKROKeyboard.press(KEY_LEFT);  
  }
  else if(code == IR_RIGHT) {
    NKROKeyboard.press(KEY_RIGHT);  
  }
  else if(code == IR_UP) {
    NKROKeyboard.press(KEY_UP);  
  }
  else if(code == IR_DOWN) {
    NKROKeyboard.press(KEY_DOWN);  
  }
  else if(code == IR_OK) {
    NKROKeyboard.press(KEY_ENTER);  
  }
  else if(code == IR_MENU) {
    NKROKeyboard.press(KEY_ENTER);  
  }
  else if(code == IR_BACK) {
    NKROKeyboard.press(KEY_ESC);  
  }
  else if(code == IR_HOME) {
    Consumer.press(CONSUMER_BROWSER_HOME);  
  }
  else if(code == IR_PLAY || code == IR_PASUE) {
    Consumer.press(MEDIA_PLAY_PAUSE);
  }
  else if(code == IR_STOP) {
    Consumer.press(MEDIA_STOP);
  }
  else if(code == IR_NEXT) {
    Consumer.press(MEDIA_NEXT);
  }
  else if(code == IR_PREVIOUS) {
    Consumer.press(MEDIA_PREVIOUS);
  }
  else if(code == IR_VOLUME_UP) {
    Consumer.press(MEDIA_VOLUME_UP);
  }
  else if(code == IR_VOLUME_DOWN) {
    Consumer.press(MEDIA_VOLUME_DOWN);
  }
  else if(code == IR_VOLUME_MUTE) {
    Consumer.press(MEDIA_VOLUME_MUTE);
  }
  else if(code == IR_SHUTDOWN) {
    Consumer.press(CONSUMER_POWER);
    System.press(SYSTEM_SLEEP);
  }
}

bool decodeAndFilter() {
  return IrReceiver.decode() 
    && IrReceiver.decodedIRData.protocol == NEC 
    && IrReceiver.decodedIRData.address == IR_REMOTE_ADDRESS;
}

void loop() {
  if (decodeAndFilter()) {
    if (STATE == LOW) { 
      STATE = HIGH;
      digitalWrite(LED_BUILTIN, HIGH);
      convertIrCodeToKeyboardKey(IrReceiver.decodedIRData.command);
    }
    
    LAST_PRESS_TIME = millis();
    LAST_KEY = IrReceiver.decodedIRData.command;
    IrReceiver.resume();
  }
  
  if (STATE == HIGH && millis() - LAST_PRESS_TIME > MAX_TIME) {
    STATE = LOW; 
    digitalWrite(LED_BUILTIN, LOW);
    NKROKeyboard.releaseAll();  
    Consumer.releaseAll();
    System.releaseAll();
  }
}
