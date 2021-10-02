#include <M5Stack.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

const int HEART_RATE_HISTORY = 150;

PulseOximeter pox;
int heartRate[HEART_RATE_HISTORY];
uint32_t tsLastReport = 0;

void onBeatDetected()
{
//    Serial.println("Beat!");
}

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);

  if (!pox.begin()) {
    M5.Lcd.println("PulseOximeter is not Started.");
    Serial.println("PulseOximeter is not Started.");
    for(;;);
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);

  for (int x = 0; x < HEART_RATE_HISTORY; x++) {
    heartRate[x] = 0;
  }
}

int getX(int i) {
  return i * 2;
}

int getY(int i) {
   return 200 - (heartRate[i] * 2);
}
void loop() {
    pox.update();
    int oldX = getX(0);
    int oldY = getY(0);
    for (int x = 0; x < HEART_RATE_HISTORY - 1; x++) {
      M5.Lcd.drawLine(oldX, oldY, getX(x+1), getY(x+1), TFT_BLACK);
      oldX = getX(x + 1);
      oldY = getY(x + 1);
      heartRate[x] = heartRate[x + 1];
    }
    heartRate[HEART_RATE_HISTORY - 1] = pox.getHeartRate();

    for (int x = 0; x < HEART_RATE_HISTORY - 1; x++) {
      M5.Lcd.drawLine(getX(x), getY(x), getX(x+1), getY(x+1), TFT_DARKGREEN);
    }

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        M5.Lcd.setCursor(5, 200); M5.Lcd.printf("Heart rate: %3.2fbpm  ", pox.getHeartRate());
        M5.Lcd.setCursor(5, 220); M5.Lcd.printf("SpO2      : %3d %%", pox.getSpO2());
        tsLastReport = millis();
    }
}
