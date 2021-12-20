#pragma once
#include "Arduino.h"
#include <Tab.h>

#define wlIcon100    5
#define wlIcon50     6
#define wlIcon25     7
#define wlIconDanger 9

int intLength ( int number ) {
    String s = String( number );
    return s.length();
}

class PlantTab : public Tab {
public: 
    String* name;
    DHTesp* dht;
    HumiditySensor* hSensor;
    Reservoir* reservoir;

    PlantTab ( String* name, DHTesp* dht, HumiditySensor* hSensor, Reservoir* reservoir ) :
        Tab( )
    { 
        this->name      = name;
        this->dht       = dht;
        this->hSensor   = hSensor;
        this->reservoir = reservoir;
    }

    void setup ( ) { }

    void draw ( void ) {
        clear( );
        
        // Name
        lcd->print( *name );

        // Time
        lcd->setCursor(14,0);
        lcd->write(0);
        lcd->write(1);
            // lcd total - length of measuring unit - length of number + 
        lcd->setCursor( 16 - 2 - intLength(Configurations::PLANT_TIME_DAYS), 0 );
        lcd->print( Configurations::PLANT_TIME_DAYS );

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

        // Reservoir
        int level = reservoir->getLevelPercentage();
        lcd->setCursor(15, 1);
        if      ( level == 100 ) lcd->write( wlIcon100 );
        else if ( level == 50  ) lcd->write( wlIcon50  );
        else if ( level == 25  ) lcd->write( wlIcon25  );
        else if ( level == 0   ) {
            lcd->setCursor(14, 1);
            lcd->print("!!");
        }
    }
    
    void identify ( void ) {
        Serial.println( "PlantTab: " + *name );
    }
};