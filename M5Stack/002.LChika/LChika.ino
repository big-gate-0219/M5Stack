#include <M5Stack.h>

#define LED_PIN 2

void setup() {
  M5.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(200);

  digitalWrite(LED_PIN, LOW);
  delay(200);
}
