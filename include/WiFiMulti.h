#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Configurations.h>

String ssid = Configurations::WIFI_NAME;
String password = Configurations::WIFI_PASSWORD;

static ESP8266WiFiMulti WiFiMulti;

void wiFiMultiInit ( ) {
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