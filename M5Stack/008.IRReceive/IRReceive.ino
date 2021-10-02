#include <M5Stack.h>
#include <IRrecv.h>
#include <IRutils.h>

#define SERIAL_BAUD_RATE 11520

const uint16_t IR_RECEIVE_PIN = 22;
const uint16_t IR_SAEND_PIN = 21;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 50;

IRrecv irrecv(IR_RECEIVE_PIN, kCaptureBufferSize, kTimeout, true);

void setup() {
  M5.begin();
  irrecv.enableIRIn();
  M5.Lcd.setTextSize(2);
}

void loop() {
  decode_results results;
  if (irrecv.decode(&results)) {
    Serial.print(resultToHumanReadableBasic(&results));
    Serial.println(results.command);
  }
  delay(1);
}
