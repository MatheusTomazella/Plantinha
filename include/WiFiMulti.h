#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

String ssid = "A";
String password = "A216191310";
IPAddress local_IP(192, 168, 15, 150);
IPAddress gateway(192, 168, 15, 1);
IPAddress subnet(255, 255, 0, 0);

static ESP8266WiFiMulti WiFiMulti;

void wiFiMultiInit ( ) {
    WiFi.config(local_IP, gateway, subnet);
    WiFi.mode(WIFI_STA);

    WiFiMulti.addAP(ssid.c_str(), password.c_str());

    while (WiFiMulti.run() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("Connected to " + ssid);
    Serial.println("IP address: " + WiFi.localIP().toString());
}