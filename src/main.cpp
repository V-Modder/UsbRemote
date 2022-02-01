#include <Arduino.h>
#include <HID-Project.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
#define LED_BUILTIN 17
uint16_t LAST_KEY;


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

void convertItCodeToKeyboardKey(int code) {
  if(code == 0x151) {
    NKROKeyboard.press(KEY_ENTER);  
  }
  else if(code == 0x161) {
    Consumer.press(MEDIA_PLAY_PAUSE);
  }

  KEY_ENTER;
  KEY_ESC;
  KEY_HOME;
  KEY_LEFT;
  KEY_RIGHT;
  KEY_UP;
  KEY_DOWN;
  KEY_LEFT_WINDOWS;
  KEY_MENU;
  KEY_MENU2;
  KEY_MUTE;
  KEY_PAUSE;
  KEY_POWER;
  KEY_RETURN;
  KEY_RIGHT_GUI;
  KEY_STOP;
  KEY_VOLUME_DOWN;
  KEY_VOLUME_UP;
  
  MEDIA_PLAY_PAUSE;
  MEDIA_NEXT;
  MEDIA_PREVIOUS;
  MEDIA_STOP;
  MEDIA_VOLUME_DOWN;
  MEDIA_VOLUME_UP;
  MEDIA_VOLUME_MUTE;
  CONSUMER_POWER;
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
