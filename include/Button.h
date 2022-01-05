#include "Arduino.h"
#include <Display.h>

class Button {
public:
    int pin;
    Display* display;
    static int holdThreshold;
    static int doublePressThreshold;

    Button ( int pin, Display* display ) {
        this->pin = pin;
        this->display = display;
        pinMode( pin, INPUT );
    }

private:
    int lastPress_length = 0;
    int lastPress_up_ts = 0;
    int press_down_ts = 0;
    int press_up_ts = 0;
    bool pressToRun = false;

public:
    void update() {
        bool pressed = digitalRead( pin ) == LOW;

        if ( pressed ) {
            if ( press_down_ts == 0 ) press_down_ts = millis();
            return;
        } else {
            if ( press_down_ts == 0 ) {
                if ( pressToRun && millis() - lastPress_up_ts > doublePressThreshold ) {
                    pressToRun = false;
                    press();
                }
                return;
            }

            press_up_ts = millis();

            int gapLength = press_down_ts - lastPress_up_ts;
            int pressLength = press_up_ts - press_down_ts;

            if ( pressLength < 25 ) return;

            lastPress_length = pressLength;
            lastPress_up_ts = press_up_ts;
            press_down_ts = press_up_ts = 0;

            if ( gapLength < doublePressThreshold ) {
                pressToRun = false;
                doublePress();
                return;
            }
            if ( pressLength > holdThreshold ) {
                hold();
                return;
            }
            pressToRun = true;
        }
    }

private:
    void press() {
        display->current->press();
    }

    void hold() { 
        display->current->hold();
    }

    void doublePress() {
        display->current->doublePress();
    }
};

int Button::holdThreshold = 800;
int Button::doublePressThreshold = 200;