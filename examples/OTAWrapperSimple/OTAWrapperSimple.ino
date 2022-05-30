/* ------------------------------------------------- */

#include "OTAWrapper.h"

/* ------------------------------------------------- */

#define SERIAL_SPEED        9600

#define AP_NAME             "AP"
#define OTA_NAME            "esp"
#define OTA_PASSWD          ""

#define WIFI_SSID       "YOUR_SSID"
#define WIFI_PWD        "YOUR_PASSWORD"

/* ------------------------------------------------- */

OTAWrapper ota;
int timeout;

/* ------------------------------------------------- */


bool connectToWiFi(const char* ssid, const char* password, int max_tries = 10) {
  int i = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (!isWiFiConnected() && i <= max_tries) {
    delay(1000);
    i++;
  }
  return isWiFiConnected();
}

/* ------------------------------------------------- */

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

/* ------------------------------------------------- */
/* ------------------------------------------------- */

void setup() {
  Serial.begin(SERIAL_SPEED);
  while (!Serial) {
    delay(20);
  }

  // this is for the "blink" sketch in the loop but with a randomized seed
  // when you reupload this sketch the blink speed will most likely be different
    #ifdef LED_BUILTIN
        pinMode(LED_BUILTIN, OUTPUT);
    #endif
  randomSeed(analogRead(0));
  timeout = (random(10) + 1) * 100;
  Serial.print("timeout: ");
  Serial.println(timeout);

  // I use the WiFi Manager to set up the connection
  // you could also do it by habd
  if (connectToWiFi(WIFI_SSID, WIFI_PWD)) {
    Serial.println("Connected to WiFi");    
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
  } else {
        Serial.println("could not connnect to WiFi");
        delay(1000);
        ESP.restart();
        delay(1000);

  }
}

/* ------------------------------------------------- */

void loop() {
  ota.loop();
  // randomized "blink" code
  #ifdef LED_BUILTIN  
    digitalWrite(LED_BUILTIN, HIGH);
  #endif
  delay(timeout);
  #ifdef LED_BUILTIN  
    digitalWrite(LED_BUILTIN, LOW);
  #endif
  Serial.print(".");
  delay(timeout);
}
/* ------------------------------------------------- */