#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("Hello World from M5Stack");

}

void loop() {
}
