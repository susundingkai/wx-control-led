#include "ESP8266.h"
#include "OurSpark.h"
ColorLEDController LEDController1(2, A2);
#ifdef ESP32
#error "This code is not recommended to run on the ESP32 platform! Please check your Tools->Board setting."
#endif

/**
**CoreUSB UART Port: [Serial1] [D0,D1]
**Core+ UART Port: [Serial1] [D2,D3]
**/
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define EspSerial Serial1
#define UARTSPEED  115200
#endif

/**
**Core UART Port: [SoftSerial] [D2,D3]
**/
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); /* RX:D2, TX:D3 */

#define EspSerial mySerial
#define UARTSPEED  9600
#endif


#define SSID        "ss"
#define PASSWORD    "ssdk1234"
#define HOST_NAME   "140.143.12.94"
#define HOST_PORT   (4000)

ESP8266 wifi(&EspSerial);
  uint8_t buffer[128] = {0};
  static uint8_t mux_id = 0;
void setup(void)
{
  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.print("setup begin\r\n");
  delay(100);

  WifiInit(EspSerial, UARTSPEED);

  Serial.print("FW Version: ");
  Serial.println(wifi.getVersion().c_str());


  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

  if (wifi.enableMUX()) {
    Serial.print("multiple ok\r\n");
  } else {
    Serial.print("multiple err\r\n");
  }

  Serial.print("setup end\r\n");
}
int k=0;
void loop(void)
{
  k=0;
  if (wifi.createTCP(mux_id, HOST_NAME, HOST_PORT)) {
    Serial.print("create tcp ");
    Serial.print(mux_id);
    Serial.println(" ok");
    k=1;
  } else {
    Serial.print("create tcp ");
    Serial.print(mux_id);
    Serial.println(" err");
    k=0;
  }


  char *hello = "arduino";
  if (wifi.send(mux_id, (const uint8_t*)hello, strlen(hello))) {
    Serial.println("send ok");
    k=1;
  } else {
    Serial.println("send err");
    k=0;
  }
  while(k==1){
  readi();
  }

  if (wifi.releaseTCP(mux_id)) {
    Serial.print("release tcp ");
    Serial.print(mux_id);
    Serial.println(" ok");
  } else {
    Serial.print("release tcp ");
    Serial.print(mux_id);
    Serial.println(" err");
  }
  mux_id++;
  if (mux_id >= 5) {
    mux_id = 0;
  }
}
 void readi(){
  uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);
  if (len > 0) {
    led(buffer);
    Serial.print("Received:[");
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
  }
 }
 void led(char *a)
 {
  if (*a=='1')
   LEDController1.ShowColor(0,255,0,0); //第一个参数表示点亮0号灯，让其显示红光
  if (*a=='2')
  LEDController1.ShowColor(0,0,255,0); //第一个参数表示点亮0号灯，让其显示绿光
  if (*a=='3')
  LEDController1.ShowColor(0,0,0,255);
  if (*a=='0')
  LEDController1.ShowColor(0,0,0,0);
 }
 
