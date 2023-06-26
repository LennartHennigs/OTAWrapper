/////////////////////////////////////////////////////////////////
/*
  ESP Library to simplify OTA setup.
  Copyright 2020 Lennart Hennigs
*/
/////////////////////////////////////////////////////////////////

#include "OTAWrapper.h"

/////////////////////////////////////////////////////////////////

OTAWrapper::OTAWrapper() {
#ifdef LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
#endif
}

/////////////////////////////////////////////////////////////////

void OTAWrapper::onStart(CallbackFunction f) {
  on_start = f;
}
  
/////////////////////////////////////////////////////////////////

void OTAWrapper::onEnd(CallbackFunction f) {
  on_end = f;
}

/////////////////////////////////////////////////////////////////

void OTAWrapper::onProgress(CallbackFunction f) {
  on_progress = f;
}

/////////////////////////////////////////////////////////////////

void OTAWrapper::onError(CallbackFunction f) {
  on_error = f;
}

/////////////////////////////////////////////////////////////////

ota_error_t OTAWrapper::getLastError() {
  return last_error;
}

/////////////////////////////////////////////////////////////////

String OTAWrapper::errorToString(ota_error_t error) {
  switch (error) {
  case OTA_AUTH_ERROR:
    return "Auth Failed";
  case OTA_BEGIN_ERROR:
    return "Begin Failed";
  case OTA_CONNECT_ERROR:
    return "Connect Failed";
  case OTA_RECEIVE_ERROR:
    return "Receive Failed";
  case OTA_END_ERROR:
    return "End Failed";
  }
  return "";
}

/////////////////////////////////////////////////////////////////


  int OTAWrapper::getProgress() {
    return progress;
  }


void OTAWrapper::setup(const char *name, const char *passwd /* = "" */, const int port /* = 8266 */) {
  ArduinoOTA.onStart([=] () {
    #ifdef LED_BUILTIN
      digitalWrite(LED_BUILTIN, LOW);
    #endif
    if (on_start != NULL) on_start();
  });
  
  ArduinoOTA.onProgress([=] (unsigned int progress, unsigned int total) {
    int p = (progress / (total / 100));
    this->progress = p;
    #ifdef LED_BUILTIN
      digitalWrite(LED_BUILTIN, (p % 2 == 1) ? HIGH : LOW); 
    #endif
    if (on_progress != NULL) on_progress();
  });
  
  ArduinoOTA.onEnd([=] () {
  #ifdef LED_BUILTIN
    digitalWrite(LED_BUILTIN, HIGH);
  #endif
  if (on_end != NULL) on_end();
    ESP.restart();
    delay(1000);
  });
  
  ArduinoOTA.onError([=] (ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    Serial.print(errorToString(error));
    last_error = error;
    if (on_error != NULL) on_error();      
  });

  ArduinoOTA.setPort(port);
  ArduinoOTA.setHostname(name);
  if (passwd != "") {
    ArduinoOTA.setPassword(passwd);
  }
  ArduinoOTA.begin();
}

/////////////////////////////////////////////////////////////////

void OTAWrapper::loop() {
  ArduinoOTA.handle();
}

/////////////////////////////////////////////////////////////////