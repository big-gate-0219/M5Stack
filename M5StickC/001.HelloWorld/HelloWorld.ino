#include <M5StickC.h>

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0,0,2);
  M5.Lcd.print("Hello World");
}

void loop() {

}
