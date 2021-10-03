#include <M5StickC.h>
#include <WiFi.h>
#include <WebServer.h>
#include <IRsend.h>

// IR Config
const uint16_t IR_SEND_PIN = GPIO_NUM_9;

// WIFI Config
const char* ssid = "Wifi_SSID";
const char* password = "Wifi_Password";

WebServer server(80);
IRsend irSend(IR_SEND_PIN);

void handleRoot() {
  server.send(200, "text/plain", "hello from M5StickC!");
  irSend.send(PANASONIC, 0x555AF148288F, 48, 0);
  Serial.println("accessed on root");
}

void handleNotFound() {
  server.send(400, "text/palin", "File Not Found");
  Serial.println("File Not Found");
}

void setup() {
  M5.begin();
  irSend.begin();

  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(1);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print('.');
  }
  M5.Lcd.println("");
  M5.Lcd.println("WiFi Connected");
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  M5.Lcd.println("HTTP server started");

}

void loop() {
  server.handleClient();
}
