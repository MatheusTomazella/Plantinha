#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Tab.h>
#include <PlantTab.h>

class Display {
public:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
    Tab* home = nullptr;
    Tab* current = nullptr;

    Display ( int addr = 0x27, int cols = 16, int rows = 2, int i2c_sda = 4, int i2c_scl = 5 ) {
        Wire.begin(i2c_sda, i2c_scl);
        lcd = LiquidCrystal_I2C(addr, cols, rows);
        lcd.init();
        lcd.setBacklight(true);
        clear();
    }   

    void clear ( ) {
        lcd.clear();
        lcd.home();
    }

    void print ( String str ) {
        lcd.print(str);
    }

    void createChar ( int id, byte* data ) {
        lcd.createChar(id, data);
    }

    void setCursor ( int col, int row ) {
        lcd.setCursor(col, row);
    }

    void addTab ( Tab* tab ) {
        tab->setLcd( &lcd );

        if ( home == nullptr ) {
            home = tab;
            current = tab;
        } else {
            Tab* t = home;
            while ( t != nullptr ) {
                if ( t->next == nullptr ) {
                    t->next = tab;
                    break;
                }
                t = t->next;
            }
        }
    }

    void nextTab ( ) {
        if ( current->next == nullptr ) current = home;
        else current = current->next;
        current->draw();
    }

    void navigateHome ( ) {
        current = home;
        current->draw();
    }

    void update ( ) {
        current->draw();
    }
};