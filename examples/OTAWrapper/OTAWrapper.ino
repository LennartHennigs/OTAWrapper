/* ------------------------------------------------- */

#include "OTAWrapper.h"
#include "WiFiManager.h"        // https://github.com/tzapu/WiFiManager

/* ------------------------------------------------- */

#define SERIAL_SPEED        9600

#define AP_NAME             "AP"
#define OTA_NAME            "esp"
#define OTA_PASSWD          ""

/* ------------------------------------------------- */

WiFiManager wifiManager;
OTAWrapper ota;

int pause;

/* ------------------------------------------------- */

void wifiSetup() {
  wifiManager.setAPCallback([] (WiFiManager * myWiFiManager) {
    Serial.println("Starting AP");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());
  });
  wifiManager.setConfigPortalTimeout(10* 60);
  if (!wifiManager.autoConnect(AP_NAME)) {
    ESP.restart();
    delay(1000);
  }
}

/* ------------------------------------------------- */
/* ------------------------------------------------- */

void setup() {
  Serial.begin(SERIAL_SPEED);

  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0));
  pause = (random(10) + 1) * 100;

  wifiSetup();
  ota.setup(OTA_NAME, OTA_PASSWD);
  
  ota.onStart([] () {
    Serial.println("OTA START");
  });
  ota.onEnd([] () {
    Serial.println("OTA END");
  });
  ota.onError([] () {
    Serial.println("OTA ERROR");
  });
}

void loop() {
  ota.loop();

  digitalWrite(LED_BUILTIN, HIGH);
  delay(pause);
  digitalWrite(LED_BUILTIN, LOW);
  delay(pause);
}
/* ------------------------------------------------- */
