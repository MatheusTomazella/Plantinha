#include "Arduino.h"
// Config
#include "config.h"
// WiFiMulti
#include <WiFiMulti.h>
// Dashboard
#include <Dashboard.h>
// DHT
#include <DHTesp.h>
// HumiditySensor
#include <HumiditySensor.h>
//Display
#include <Display.h>
#include <customChars.h>
#include <PlantTab.h>
#include <IpTab.h>
//Button
#include <Button.h>
// Testing Client wifi
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 
int soilSensorPin;
int pumpPin;
int buttonPin = 0;
int wl100;
int wl50;
int wl25;

Display display(0x27,16,2);

DHTesp dht;

HumiditySensor hSensor( A0, 5/*%*/ );

Dashboard dashboard(&dht, &hSensor);

Button button( buttonPin, &display );
 
void setup( void ) {
	/* Serial */

	Serial.begin(9600);

	/* WiFi */
	wiFiMultiInit();

	/* Testing Shit */
	WiFiClient client;
	
	Serial.println( client.connect( "google.com", 80 ) );

	Serial.println( client.println( "GET /search?q=arduino HTTP/1.0" ) );

	pinMode( D5, OUTPUT );

	/* Dashboard */
	dashboard.init();

	/* DHT */
	dht.setup(16, DHTesp::DHT11);

	/* Display */
	display.createChar(0, charDi);
	display.createChar(1, charAs);
	display.createChar(2, charCelsius);
	display.createChar(3, charPlant);
	display.createChar(4, charWind);

	display.addTab( new PlantTab( "Planta", &dht, &hSensor ) );
	display.addTab( new IpTab( &dashboard ) );
}

int displayTimer = millis();
void loop( void ) {
	dashboard.listen();

	if ( millis() - displayTimer >= DISPLAY_REFRESH_RATE ) {
		display.update();
		displayTimer = millis();
	}

	button.update();
}
