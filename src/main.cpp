#include <Arduino.h>
#include <HID-Project.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
#define LED_BUILTIN 17

#define IR_LEFT 0x511
#define IR_RIGHT 0x511
#define IR_UP 0x511
#define IR_DOWN 0x511
#define IR_OK 0x511
#define IR_MENU 0x511
#define IR_BACK 0x511
#define IR_HOME 0x511
#define IR_PLAY_PASUE 0x511
#define IR_STOP 0x511
#define IR_NEXT 0x511
#define IR_PREVIOUS 0x511
#define IR_VOLUME_UP 0x511
#define IR_VOLUME_DOWN 0x511
#define IR_VOLUME_MUTE 0x511
#define IR_SHUTDOWN 0x511

unsigned int LAST_KEY;


void setup() {
  Serial.begin(115200);
  Serial.println("UsbRemote starting...");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);

  IrReceiver.begin(IR_RECEIVE_PIN, true, LED_BUILTIN);

  NKROKeyboard.begin();
  Consumer.begin();
}

void convertItCodeToKeyboardKey(unsigned int code) {
  if(code == IR_LEFT) {
    NKROKeyboard.write(KEY_LEFT);  
  }
  else if(code == IR_RIGHT) {
    NKROKeyboard.write(KEY_RIGHT);  
  }
  else if(code == IR_UP) {
    NKROKeyboard.write(KEY_UP);  
  }
  else if(code == IR_DOWN) {
    NKROKeyboard.write(KEY_DOWN);  
  }
  else if(code == IR_OK) {
    NKROKeyboard.write(KEY_ENTER);  
  }
  else if(code == IR_MENU) {
    NKROKeyboard.press(KEY_ENTER);  
    delay(2000);
    NKROKeyboard.release(KEY_ENTER);  
  }
  else if(code == IR_BACK) {
    NKROKeyboard.write(KEY_ESC);  
  }
  else if(code == IR_HOME) {
    NKROKeyboard.write(KEY_HOME);  
  }
  else if(code == IR_PLAY_PASUE) {
    Consumer.write(MEDIA_PLAY_PAUSE);
  }
  else if(code == IR_STOP) {
    Consumer.write(MEDIA_STOP);
  }
  else if(code == IR_NEXT) {
    Consumer.write(MEDIA_NEXT);
  }
  else if(code == IR_PREVIOUS) {
    Consumer.write(MEDIA_PREVIOUS);
  }
  else if(code == IR_VOLUME_UP) {
    Consumer.write(MEDIA_VOLUME_DOWN);
  }
  else if(code == IR_VOLUME_DOWN) {
    Consumer.write(MEDIA_VOLUME_UP);
  }
  else if(code == IR_VOLUME_MUTE) {
    Consumer.write(MEDIA_VOLUME_MUTE);
  }
  else if(code == IR_SHUTDOWN) {
    Consumer.write(CONSUMER_POWER);
  }
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT == IRDATA_FLAGS_IS_REPEAT) {
      IrReceiver.decodedIRData.command = LAST_KEY;
    }

    Serial.println(IrReceiver.decodedIRData.command, HEX);
    switch (IrReceiver.decodedIRData.protocol) {
      case NEC:
        Serial.println("NEC");
        break;
      case SONY:
        Serial.println("SONY");
        break;
      case RC5:
        Serial.println("RC5");
        break;
      case RC6:
        Serial.println("RC6");
        break;
      case DISH:
        Serial.println("DISH");
        break;
      case SHARP:
        Serial.println("SHARP");
        break;
      case JVC:
        Serial.println("JVC");
        break;
      case SAMSUNG:
        Serial.println("SAMSUNG");
        break;
      case LG:
        Serial.println("LG");
        break ;
      case WHYNTER:
        Serial.println("WHYNTER");
        break;
      case PANASONIC:
        Serial.println("PANASONIC");
        break;
      case DENON:
        Serial.println("DENON");
        break;
      case BOSEWAVE:
        Serial.println("BOSEWAVE");
        break;
      case LEGO_PF:
        Serial.println("LEGO_PF");
        break;
      case MAGIQUEST:
        Serial.println("MAGIQUEST");
        break;
      default:
      case UNKNOWN:
        Serial.println("UNKNOWN");
        break;
    }
    
    convertItCodeToKeyboardKey(IrReceiver.decodedIRData.command);
    LAST_KEY = IrReceiver.decodedIRData.command;
    IrReceiver.resume();
  }
}
