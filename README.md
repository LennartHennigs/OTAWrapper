OTAWrapper
==========

* Author: Lennart Hennigs (https://www.lennarthennigs.de)
* Copyright (C) 2021 Lennart Hennigs.
* Released under the MIT license.


Description
-----------

This class maked it easier to implement the OTA functionality.

- It offers callback functions for tracking the OTA events.
- You can get the progress count and implement your own status display.
- It tries to use the builtin LED to show the update status


- **Note:** For the class to work, you need to call the `loop()` member function in your sketch's `loop()` function. See the example for more details.

How to Use
----------

These are the constructor and the member functions the library provides:


```
OTAWrapper();
   
void onStart(CallbackFunction f);  
void onEnd(CallbackFunction f);
void onError(CallbackFunction f);
void onProgress(CallbackFunction f);

int getProgress();

String errorToString(ota_error_t error);
ota_error_t getLastError();

void setup(char *name, char *passwd = "", int port = 8266);
void loop();

```
