#pragma once
#include "Arduino.h"

class HumiditySensor {
private:
    int pin;
    int* threshold;

public:
    HumiditySensor( );
    HumiditySensor ( int pin, int* thresholdPercentage ) {
        this->pin = pin;
        this->threshold = thresholdPercentage;
        pinMode(pin, INPUT);
    }
    
    int getAnalog ( ) {
        return 1024 - analogRead(pin);
    }

    int getPercentage ( ) {
        return floor( getAnalog() * 100 / 1024 );
    }

    int isDry ( ) {
        return getAnalog() <= *threshold;
    }
};