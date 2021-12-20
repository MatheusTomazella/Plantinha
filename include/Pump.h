#pragma once
#include "Arduino.h"
#include <Configurations.h>
#include <HumiditySensor.h>

class Pump {
private:
    int pin;
    HumiditySensor* hSensor;
    int lastRun;

public:
    Pump ( int pin, HumiditySensor* hSensor ) : 
        pin(pin), hSensor(hSensor)
    {
        pinMode( pin, OUTPUT );
        checkDry();
    }

    void check ( ) {
        if ( millis() - lastRun >= Configurations::PUMP_CHECK_INTERVAL_MS ) {
            checkDry();
        }
    }

    void checkDry ( ) {
        if ( hSensor->isDry() ) run();
    }

    void run ( ) {
        digitalWrite( pin, HIGH );
        delay( Configurations::PUMP_RUN_TIME_MS );
        digitalWrite( pin, LOW );
        lastRun = millis();
    }
};