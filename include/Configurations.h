#pragma once
#include "Arduino.h"

class Configurations { 
public:    
    Configurations ( ) {
        load();
    }

    static long unsigned int PUMP_CHECK_INTERVAL_MS;
    static long unsigned int PUMP_RUN_TIME_MS;
    static int               DRY_THRESHOLD_PERCENTAGE;
    static long unsigned int DISPLAY_REFRESH_RATE;
    static String            PLANT_NAME;
    static int               PLANT_TIME_DAYS;

    static void load ( ) { }
    static void save ( ) { }
};

long unsigned int Configurations::PUMP_CHECK_INTERVAL_MS   = 1000 * 5;
long unsigned int Configurations::PUMP_RUN_TIME_MS         = 1000 * 5;
int               Configurations::DRY_THRESHOLD_PERCENTAGE = 5;
long unsigned int Configurations::DISPLAY_REFRESH_RATE     = 1000 * 5;
String            Configurations::PLANT_NAME               = "Rogerio";
int               Configurations::PLANT_TIME_DAYS          = 192;