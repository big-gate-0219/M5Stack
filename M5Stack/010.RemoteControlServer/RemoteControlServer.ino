#include <M5Stack.h>
#include <IRsend.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>
#include "ConfigUtil.h"

const uint16_t IR_SEND_PIN = 21;

const String CONFIG_PATH_WIFI = "/wifi.conf";
const String CONFIG_KEY_WIFI_SSID = "wifi_ssid";
const String CONFIG_KEY_WIFI_PASSWORD = "wifi_pass";

const String CONFIG_PATH_IRDATA = "/irdata.conf";

ConfigUtil wifiConfig;
ConfigUtil irDataConfig;
WebServer server(80);
IRsend irSend(IR_SEND_PIN);

void toCharArray(String str, char* c) {
  str.toCharArray(c, str.length() + 1);
}

decode_type_t toProtocol(String strProtocol) {
  if (strProtocol == "PANASONIC") return PANASONIC;
  return UNKNOWN;
}

uint64_t convertStringToU64(String str) {
  String HEX_STRING = "0123456789ABCDEF";
  uint64_t val = 0;
  for (int i = 0; i < str.length(); i++) {
    val = val * 16 + HEX_STRING.indexOf(str[i]);
  }
  return val;
}

void sendIRData(String irDataText) {
  int from = 0;
  String irData[4];

  for (int i = 0; i < 4; i++) {
    int to = irDataText.indexOf(",",from);
    irData[i] = irDataText.substring(from, to);
    from = to + 1;
  }
  
  decode_type_t type = toProtocol(irData[0]);
  uint64_t code = convertStringToU64(irData[1]);
  uint16_t nbits=irData[2].toInt();
  uint16_t repeats=irData[3].toInt();
  
  irSend.send(type, code, nbits, repeats);
}

void handleRoot() {
  String path="/index.html";
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path,"r");
    server.streamFile(file,"text/html");
    file.close();
  } else {
    Serial.println("handleFileRead: 404 not found");
    server.send (404, "text/plain", "ESP: 404 not found");
  }
}

void handleSendIRData() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "btnid") {
      String btnId = server.arg(i);
      String irDataText = irDataConfig.getConfig(btnId);
      sendIRData(irDataText);
      break;
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleNotFound() {
  server.send(400, "text/palin", "File Not Found");
  Serial.println("File Not Found");
}

void setup() {
  M5.begin();
  SPIFFS.begin();
  irSend.begin();
  M5.Lcd.setTextSize(2);

  irDataConfig.loadConfig(CONFIG_PATH_IRDATA);

  char ssid[30], password[30];
  wifiConfig.loadConfig(CONFIG_PATH_WIFI);
  toCharArray(wifiConfig.getConfig(CONFIG_KEY_WIFI_SSID), ssid);
  toCharArray(wifiConfig.getConfig(CONFIG_KEY_WIFI_PASSWORD), password);  

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print('.');
  }
  MDNS.begin("m5stack");

  server.on("/", handleRoot);
  server.on("/send_ir_data", handleSendIRData);
  server.onNotFound(handleNotFound);
  server.begin();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("RemoCon:" + WiFi.localIP().toString());
  M5.Lcd.qrcode("http://"+WiFi.localIP().toString()+"/", 50, 30, 200, 4);
}

void loop() {
  server.handleClient();
}
