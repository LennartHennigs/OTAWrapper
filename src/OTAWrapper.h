/////////////////////////////////////////////////////////////////
/*
  ESP Library to simplify OTA setup.
  Copyright 2020 Lennart Hennigs
*/
/////////////////////////////////////////////////////////////////
#pragma once

#ifndef OTAWrapper_h
#define OTAWrapper_h
/////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "ArduinoOTA.h"

/////////////////////////////////////////////////////////////////

class OTAWrapper { 
 protected:
    ota_error_t last_error;
    int progress = 0;

   typedef void (*CallbackFunction) ();

   CallbackFunction on_start = NULL;
   CallbackFunction on_end= NULL;
   CallbackFunction on_error = NULL;
   CallbackFunction on_progress = NULL;

 public:
   OTAWrapper();
   
   void onStart(CallbackFunction f);  
   void onEnd(CallbackFunction f);
   void onError(CallbackFunction f);
   void onProgress(CallbackFunction f);

  int getProgress();

   String errorToString(ota_error_t error);
   ota_error_t getLastError();
   
   void setup(const char *name, const char *passwd = "", const int port = 8266);
   void loop();
};
/////////////////////////////////////////////////////////////////
#endif
/////////////////////////////////////////////////////////////////
