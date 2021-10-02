#include <M5Stack.h>

#define LM61BIZ_PIN 35

void setup() {
  M5.begin();
  pinMode(LM61BIZ_PIN, INPUT);

  M5.Lcd.setTextSize(4);
}

void loop() {
  int e = analogRead(LM61BIZ_PIN);

  float Vout = e / 4095.0 * 3.3 + 0.1132;
  float temp = (Vout - 0.6) / 0.01;
  M5.Lcd.setCursor(80, 100);
  M5.Lcd.print(temp, 1);
  M5.Lcd.print("'C");
  delay(1000);
}
