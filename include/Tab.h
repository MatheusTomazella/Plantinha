#pragma once
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include <displayEventQueue.h>

class Tab {
public:
    LiquidCrystal_I2C* lcd;
    Tab* next;

    Tab ( ) {
        next = nullptr;
    }

    Tab ( LiquidCrystal_I2C* lcd ) {
        this->lcd = lcd;
        next = nullptr;
    }

    void setLcd ( LiquidCrystal_I2C* lcd ) {
        this->lcd = lcd;
    }

    void clear ( ) {
        lcd->clear();
        lcd->home();
        lcd->setCursor(0, 0);
    }

    virtual void setup    ( ) = 0;
    virtual void draw     ( ) = 0;
    virtual void identify ( ) = 0;

    virtual void press ( ) {
        addToDisplayEventQueue( DisplayEvent_NextTab );
    }
    virtual void hold ( ) {
        addToDisplayEventQueue( DisplayEvent_NavigateHome );
    }
    virtual void doublePress ( ) {
        identify();
    }
};