#pragma once

#ifndef OTAWrapper_h
#define OTAWrapper_h

#include <ArduinoOTA.h>

class OTAWrapper { 
 private:
   ota_error_t last_error;

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

   ota_error_t getLastError();
   
   void setup(char *name, char *passwd = "", int port = 8266);
   void loop();
}

#endif
