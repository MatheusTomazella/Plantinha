#include "Arduino.h"
// Config
#include "config.h"
#include "Configurations.h"
// WiFiMulti
#include <WiFiMulti.h>
// Dashboard
#include <Dashboard.h>
// DHT
#include <DHTesp.h>
// HumiditySensor
#include <HumiditySensor.h>
// Reservoir
#include <Reservoir.h>
// Pump
#include <Pump.h>
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
 
int soilSensorPin = A0;
int pumpPin 	  = D5;
int buttonPin 	  = 0;
int wl100 		  = D6;
int wl50 		  = D7;
int wl25 		  = D8;

Display display(0x27,16,2);

DHTesp dht;

HumiditySensor hSensor( soilSensorPin, &Configurations::DRY_THRESHOLD_PERCENTAGE );

Reservoir reservoir( wl25, wl50, wl100 );

Pump pump( pumpPin, &hSensor );

Dashboard dashboard(&dht, &hSensor, &reservoir);

Button button( buttonPin, &display );
 
void setup( void ) {
	/* Configurations */
	Configurations::load();

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
	display.createChar( 0, charDi 	     );
	display.createChar( 1, charAs 	     );
	display.createChar( 2, charCelsius   );
	display.createChar( 3, charPlant     );
	display.createChar( 4, charWind      );
	display.createChar( 5, charLvl100    );
	display.createChar( 6, charLvl50     );
	display.createChar( 7, charLvl25     );

	display.addTab( new PlantTab( &Configurations::PLANT_NAME, &dht, &hSensor, &reservoir ) );
	display.addTab( new IpTab( &dashboard ) );
}

int displayTimer = millis();
void loop( void ) {
	dashboard.listen();

	if ( millis() - displayTimer >= Configurations::DISPLAY_REFRESH_RATE ) {
		display.update();
		displayTimer = millis();
	}

	button.update();

	pump.check();
}
