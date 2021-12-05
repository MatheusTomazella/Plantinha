#pragma once
#include "Arduino.h"
#include <Tab.h>
#include <Dashboard.h>

class IpTab : public Tab {
public:
    Dashboard* dashboard;

    IpTab ( Dashboard* dashboard ) : 
        Tab ( )
    {
        this->dashboard = dashboard;
    }

    void setup ( ) { }

    void draw ( ) {
        clear();
        lcd->print( dashboard->getIp() );
    }

    void identify ( void ) {
        Serial.println( "IpTab: " + dashboard->getIp() );
    }
};