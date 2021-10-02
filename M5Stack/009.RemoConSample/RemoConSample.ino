#include <M5Stack.h>
#include <IRsend.h>

enum RemoconMode {
  Volume,
  Channel
};

const uint16_t IR_SEND_PIN = 21;

enum RemoconMode mode = Volume;
IRsend irSend(IR_SEND_PIN);

void drawVolumeMode() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRoundRect(  0, 198, 100, 40, 4, BLUE);
  M5.Lcd.drawRoundRect(110, 198, 100, 40, 4, BLUE);
  M5.Lcd.drawRoundRect(220, 198, 100, 40, 4, BLUE);
  M5.Lcd.setCursor(0, 0); M5.Lcd.print("Mode : Volume");
  M5.Lcd.setCursor( 40,206);M5.Lcd.print("-");
  M5.Lcd.setCursor(127,206);M5.Lcd.print("Mode");
  M5.Lcd.setCursor(260,206);M5.Lcd.print("+");
}

void drawChannelMode() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawRoundRect(  0, 198, 100, 40, 4, BLUE);
  M5.Lcd.drawRoundRect(110, 198, 100, 40, 4, BLUE);
  M5.Lcd.drawRoundRect(220, 198, 100, 40, 4, BLUE);
  M5.Lcd.setCursor(0, 0); M5.Lcd.print("Mode : Channel");
  M5.Lcd.setCursor( 15,206);M5.Lcd.print("Down");
  M5.Lcd.setCursor(127,206);M5.Lcd.print("Mode");
  M5.Lcd.setCursor(250,206);M5.Lcd.print("Up");

}

void setup() {
  M5.begin();
  irSend.begin();
  M5.Lcd.setTextSize(3);

  mode = Volume;
  drawVolumeMode();
}

void loop() {
  M5.update();

  if (M5.BtnA.isPressed()) {
    if (mode == Volume) {
      irSend.send(PANASONIC, 0x555AF148A887, 48, 0);
    } else if (mode = Channel) {
      irSend.send(PANASONIC, 0x555AF1484889, 48, 0);
    }
  }
  if (M5.BtnC.isPressed()) {
     if(mode == Volume) {
      irSend.send(PANASONIC, 0x555AF148288F, 48, 0);
     } else if (mode = Channel) {
      irSend.send(PANASONIC, 0x555AF1488885, 48, 0);
     }
  }

  if (M5.BtnB.wasPressed()) {
     if (mode == Volume) {
        mode = Channel;
        drawChannelMode();
     } else if (mode = Channel) {
        mode = Volume;
        drawVolumeMode();
     } else {
        mode = Volume;
        drawVolumeMode();
     }
  }
  delay(100);
}
