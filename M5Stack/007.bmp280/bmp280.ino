#include <M5Stack.h>
#include "Seeed_BMP280.h"
#include <Wire.h>

BMP280 bmp280;

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
  if (!bmp280.init()) {
    Serial.println("Device not connected or broken!");
    while (true);
  }
}

void loop() {
  float bmp280temp = bmp280.getTemperature();
  uint32_t pressure = bmp280.getPressure();
  float altitude = bmp280.calcAltitude(pressure);
  M5.Lcd.setCursor(40, 110); M5.Lcd.printf("Temp: %5.1f'C", bmp280temp);
  M5.Lcd.setCursor(40, 150); M5.Lcd.printf("Press: %dhPa", pressure / 100);
  M5.Lcd.setCursor(40, 190); M5.Lcd.printf("Alti: %5.2fm", altitude);
  delay(1000);
}
