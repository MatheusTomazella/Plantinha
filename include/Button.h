#include "Arduino.h"
#include <Display.h>

class Button {
public:
    int pin;
    Display* display;

    Button ( int pin, Display* display ) {
        this->pin = pin;
        this->display = display;
        pinMode( pin, INPUT );
    }

    void update() {
        if ( digitalRead( pin ) == LOW ) {
            if ( timeOfPress == 0 ) timeOfPress = millis();
        } else
            if ( timeOfPress != 0 ) {
                bool isHold = millis() - timeOfPress > 1000;
                timeOfPress = 0;
                if ( isHold ) hold();
                else press();
            }
    }

private:
    int timeOfPress = 0;

    void press() {
        display->nextTab();
    }

    void hold() { 
        display->navigateHome();
    }
};