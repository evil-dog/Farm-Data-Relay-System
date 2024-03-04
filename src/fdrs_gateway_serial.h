#ifndef __FDRS_GATEWAY_SERIAL_h__
#define __FDRS_GATEWAY_SERIAL_h__

#include <ArduinoJson.h>

#if defined (ESP32)
#define UART_IF Serial1
#else
#define UART_IF Serial
#endif

#if defined(ESP32)
#if !defined RXD2 or !defined TXD2
    #warning Defining RXD2 and TXD2 using MCU defaults.
    #if CONFIG_IDF_TARGET_ESP32
        #define RXD2 14
        #define TXD2 15
    #elif CONFIG_IDF_TARGET_ESP32S2 or CONFIG_IDF_TARGET_ESP32S3
        #define RXD2 18
        #define TXD2 17
    #elif CONFIG_IDF_TARGET_ESP32C3
        #define RXD2 2
        #define TXD2 3
    #else
        #error MCU not supported.
    #endif
#endif
#endif

void getSerial() {
  String incomingString;
  if (UART_IF.available()){
   incomingString =  UART_IF.readStringUntil('\n');
  }
  else if (Serial.available()){
   incomingString =  Serial.readStringUntil('\n');
  }
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, incomingString);
  if (error) {    // Test if parsing succeeds.
        DBG("json parse err");
        DBG1(incomingString);
    return;
  } else {
    int s = doc.size();
    //UART_IF.println(s);
    for (int i = 0; i < s; i++) {
      theData[i].id = doc[i]["id"];
      theData[i].t = doc[i]["type"];
      theData[i].d = doc[i]["data"];
    }
    ln = s;
    newData = event_serial;
    DBG("Incoming Serial.");

  }
}

void sendSerial() {
  DBG("Sending Serial.");
  JsonDocument doc;
  for (int i = 0; i < ln; i++) {
    doc[i]["id"]   = theData[i].id;
    doc[i]["type"] = theData[i].t;
    doc[i]["data"] = theData[i].d;
  }
  serializeJson(doc, UART_IF);
  UART_IF.println();

#ifndef ESP8266
  serializeJson(doc, Serial);
  Serial.println();
#endif

}
void handleSerial(){
  while (UART_IF.available() || Serial.available())
  {
    getSerial();
  }
}

#endif //__FDRS_GATEWAY_SERIAL_h__