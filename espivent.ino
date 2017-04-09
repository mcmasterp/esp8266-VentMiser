
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <fauxmoESP.h>
#include <ESPAsyncTCP.h>
#define SERIAL_BAUDRATE                 115200
char state2Val;
fauxmoESP fauxmo;
 
void wifiSetup() {
 
    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);
 
    // Connect
    Serial.printf("[WIFI] Connecting to %s ", "FiOS-SGVFL");
    WiFi.begin("FiOS-SGVFL", "jib7584rows3699tan");
    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
 
    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
 
}
void setup() {
  // put your setup code here, to run once:
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println();
 
    // Wifi
    wifiSetup();
 
    // Fauxmo v2.0 vent "open" command
    fauxmo.addDevice("vent");
    fauxmo.onMessage([](unsigned char device_id, const char * device_name, bool state) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s\n", device_id, device_name, state ? "ON" : "OFF");
      String state2Val = String(state ? "ON" : "OFF");
      digitalWrite(2, !state);
      delay(3000);                  // waits for 3 second
      digitalWrite(2, state);
    });
         
}

void loop() {
  // put your main code here, to run repeatedly:
    fauxmo.handle();
}
