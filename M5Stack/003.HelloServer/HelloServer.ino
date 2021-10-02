#include <M5Stack.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "Wifi_SSID";
const char* password = "Wifi_PASSWORD";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from M5Stack!");
  M5.Lcd.println("accessed on root");
}

void handleNotFound() {
  server.send(400, "text/palin", "File Not Found");
  M5.Lcd.println("File Not Found");
}

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print('.');
  }
  M5.Lcd.println("");
  M5.Lcd.println("WiFi Connected");
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());

  if (MDNS.begin("m5stack")) {
    M5.Lcd.println("MDNS responder startted");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  M5.Lcd.println("HTTP server started");

}

void loop() {
   server.handleClient();
}
