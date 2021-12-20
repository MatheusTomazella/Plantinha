#pragma once
#include "Arduino.h"

class Reservoir { 
private:
    int pin25, pin50, pin100;

public:

    Reservoir ( int pin25, int pin50, int pin100 ) :
        pin25(pin25), pin50(pin50), pin100(pin100)
    {
        pinMode( pin25, INPUT );
        pinMode( pin50, INPUT );
        pinMode( pin100, INPUT );
    }

    int getLevelPercentage ( ) {
        if ( digitalRead( pin100 ) == LOW ) return 100;
        if ( digitalRead( pin50 )  == LOW ) return 50;
        if ( digitalRead( pin25 )  == LOW ) return 25;
        return 0;
    }
};