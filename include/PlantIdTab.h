#include <Tab.h>
#include <Configurations.h>

class PlantIdTab : public Tab {
public:
    void setup ( ) { }

    void draw ( void ) {
        clear();
        lcd->print( "Plant ID: " );
        lcd->print( Configurations::PLANT_ID );
    }

    void identify ( void ) {
        Serial.println( "PlantIdTab: " + String( Configurations::PLANT_ID ) );
    }

    void press ( void ) {
        Configurations::PLANT_ID++;
        draw( );
    }
    void doublePress ( void ) {
        if ( Configurations::PLANT_ID - 1 >= 0 ) Configurations::PLANT_ID--;
        draw( );
    }
    void hold ( void ) {
        addToDisplayEventQueue( DisplayEvent_NextTab );
    }
};