#define M5STACK_MPU6886
#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.IMU.Init();
  Wire.begin();
  M5.Lcd.setTextSize(2);
}

void loop() {
  float accX = 0.0f;
  float accY = 0.0f;
  float accZ = 0.0f;
  M5.IMU.getAccelData(&accX, &accY, &accZ);

  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0); M5.Lcd.print("MPU6886 acceleration");
  M5.Lcd.setCursor(0, 32); M5.Lcd.printf("X: %7.2f mG", 1000 * accX);
  M5.Lcd.setCursor(0, 64); M5.Lcd.printf("Y: %7.2f mG", 1000 * accY);
  M5.Lcd.setCursor(0, 96); M5.Lcd.printf("Z: %7.2f mG", 1000 * accZ);
  delay(2000);
}
