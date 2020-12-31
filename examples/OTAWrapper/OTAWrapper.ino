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

  // this is for the "blink" sketch in the loop but with a randomized seed
  // when you reupload this sketch the blink speed will most likely be different
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0));
  pause = (random(10) + 1) * 100;

  // I use the WiFi Manager to set up the connection
  // you could also do it by habd
  wifiSetup();
  ota.setup(OTA_NAME, OTA_PASSWD);
  
  ota.onStart([] () {
    Serial.println("OTA START");
  });
  ota.onEnd([] () {
    Serial.println(".");
    Serial.println("OTA END");
  });
  ota.onError([] () {
    Serial.println("OTA ERROR");
  });
   ota.onProgress([] () {
     int p = ota.getProgress();
     if (p % 5 == 0) {
       Serial.print(".");
     }
  });
}

void loop() {
  ota.loop();
  // randomized "blink" code
  digitalWrite(LED_BUILTIN, HIGH);
  delay(pause);
  digitalWrite(LED_BUILTIN, LOW);
  delay(pause);
}
/* ------------------------------------------------- */
