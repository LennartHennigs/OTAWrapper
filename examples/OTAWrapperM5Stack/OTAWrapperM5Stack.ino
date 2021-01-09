///////////////////////////////////////////////////////////////

#include <WiFi.h>
#include "M5Stack.h"
#include "OTAWrapper.h"

///////////////////////////////////////////////////////////////

#define SERIAL_SPEED  9600

#define OTA_NAME        "M5Stack"
#define OTA_PASSWD      ""

#define WIFI_SSID       "YOUR_SSID"
#define WIFI_PWD        "YOUR_PASSOWRD"

///////////////////////////////////////////////////////////////

OTAWrapper ota;

///////////////////////////////////////////////////////////////

bool connectToWifi(const char* ssid, const char* password, int max_tries = 10) {
  int i = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (!isWiFiConnected() && i <= max_tries) {
    delay(1000);
    i++;
  }
  return isWiFiConnected();
}

///////////////////////////////////////////////////////////////

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

///////////////////////////////////////////////////////////////

void setupSerial(long speed) {
  Serial.begin(speed);
  while (!Serial) {
    delay(50);
  }
  Serial.println();
  Serial.println();
}

///////////////////////////////////////////////////////////////

void setupOTA() {
  ota.setup(OTA_NAME, OTA_PASSWD);
  ota.onStart([]() {
    M5.Lcd.clear(0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor((320 - M5.Lcd.textWidth("OTA Update"))/2, 40);
    M5.Lcd.print("OTA Update");
  });
  ota.onProgress([]() {
    M5.Lcd.progressBar(40, 110, 240, 20, ota.getProgress());
  });
}

///////////////////////////////////////////////////////////////

void setup() {
  M5.begin(true, false, true);
  M5.Power.begin();
  M5.Speaker.mute();

  setupSerial(SERIAL_SPEED);
  Serial.println("M5 Test");

if(!connectToWifi(WIFI_SSID, WIFI_PWD)) {
    Serial.println("Could not connect to WiFi");
    Serial.println("reboot in 2 sec.");
    delay(5000);
    ESP.restart();  
  
  } else {
    Serial.print("connected to WiFi: ");
    Serial.println(WIFI_SSID);
    Serial.println(WiFi.localIP());
    setupOTA();
  }
}

///////////////////////////////////////////////////////////////

void loop() {
  M5.update();
  ota.loop();
  dacWrite(25, 0);
}

///////////////////////////////////////////////////////////////