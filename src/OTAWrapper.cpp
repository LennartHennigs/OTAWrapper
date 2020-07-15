#include "OTAWrapper.h"

OTAWrapper::OTAWrapper() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void OTAWrapper::onStart(CallbackFunction f) {
  on_start = f;
}
  
void OTAWrapper::onEnd(CallbackFunction f) {
    on_end = f;
}

void OTAWrapper::onProgress(CallbackFunction f) {
    on_progress = f;
}

void OTAWrapper::onError(CallbackFunction f) {
    on_error = f;
}

ota_error_t OTAWrapper::getLastError() {
  return last_error;
}

void OTAWrapper::setup(char *name, char *passwd /* = "" */, int port /* = 8266 */) {
    ArduinoOTA.onStart([=] () {
      digitalWrite(LED_BUILTIN, LOW);
      if (on_start != NULL) on_start();
    });
  
    ArduinoOTA.onProgress([] (unsigned int progress, unsigned int total) {
      int p = (progress / (total / 100));
      digitalWrite(LED_BUILTIN, (p % 2 == 1) ? HIGH : LOW); 
      if (on_progress != NULL) on_progress();
    });
  
    ArduinoOTA.onEnd([=] () {
      digitalWrite(LED_BUILTIN, HIGH);
      if (on_end != NULL) on_end();
      ESP.restart();
      delay(1000);
    });
  
    ArduinoOTA.onError([=] () {
      last_error = error;
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
      if (on_error != NULL) on_error();      
    });

    ArduinoOTA.setPort(port);
    ArduinoOTA.setHostname(name);
    if (passwd != "") {
      ArduinoOTA.setPassword(passwd);
    }
    ArduinoOTA.begin();
  }

  void OTAWrapper::loop() {
    ArduinoOTA.handle();
  }