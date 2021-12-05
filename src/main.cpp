#include "Arduino.h"
// Dashboard
#include <Dashboard.h>
// DHT
#include <DHTesp.h>
//Display
#include <Display.h>
#include <customChars.h>
#include <PlantTab.h>
#include <IpTab.h>
//Button
#include <Button.h>
// Time
#include <TimeApi.h>
 
int soilSensorPin;
int pumpPin;
int buttonPin = 0;
int wl100;
int wl50;
int wl25;

Display display(0x27,16,2);

DHTesp dht;

//Dashboard dashboard(&dht);

Button button( buttonPin, &display );
 
void setup(void) {
  /* Serial */

  Serial.begin(9600);

  /* Dashboard */

  //dashboard.init();



  /* DHT */
  dht.setup(16, DHTesp::DHT11);

  /* Display */
  display.createChar(0, charDi);
  display.createChar(1, charAs);
  display.createChar(2, charCelsius);
  display.createChar(3, charPlant);
  display.createChar(4, charWind);
  
  display.addTab( new PlantTab( "Planta", &dht ) );
  //display.addTab( new IpTab( &dashboard ) );
}

int displayTimer = millis();
void loop(void) {
  //dashboard.listen();
  
  if ( millis() - displayTimer >= 1000*5 ){
    display.update();
    displayTimer = millis();
  }

  button.update();
}
