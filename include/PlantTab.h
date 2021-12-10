#pragma once
#include "Arduino.h"
#include <Tab.h>

class PlantTab : public Tab {
public: 
    String name;
    DHTesp* dht;
    HumiditySensor* hSensor;

    PlantTab ( String name, DHTesp* dht, HumiditySensor* hSensor ) :
        Tab( )
    { 
        this->name    = name;
        this->dht     = dht;
        this->hSensor = hSensor;
    }

    void setup ( ) { }

    void draw ( void ) {
        clear( );
        
        // Name
        lcd->print( name );

        // Time
        lcd->setCursor(14,0);
        lcd->write(0);
        lcd->write(1);

        // Sensors
        lcd->setCursor(0,1);
        TempAndHumidity lastValues = dht->getTempAndHumidity();

        // Temperature
        if (lastValues.temperature < 10) lcd->print("0");
        lcd->print(String(lastValues.temperature,0));
        lcd->write(2);

        // Humidity
        lcd->print(" ");
        lcd->write(4);
        if (lastValues.humidity < 10) lcd->print("0");
        lcd->print(String(lastValues.humidity,0));
        lcd->print("% ");

        // Humidity Sensor
        lcd->write(3);
        if (hSensor->getPercentage() < 10) lcd->print("0");
        lcd->print(String(hSensor->getPercentage()));
        lcd->print("% ");
    }
    
    void identify ( void ) {
        Serial.println( "PlantTab: " + name );
    }
};