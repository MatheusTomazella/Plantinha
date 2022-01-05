#pragma once
#include "Arduino.h"

class Configurations { 
public:    
    Configurations ( ) {
        load();
    }

    static String            WIFI_NAME;
    static String            WIFI_PASSWORD;
    static String            API_URL;
    static long unsigned int PUMP_CHECK_INTERVAL_MS;
    static unsigned int      PUMP_RUN_TIME_MS;
    static int               DRY_THRESHOLD_PERCENTAGE;
    static unsigned int      DISPLAY_REFRESH_RATE;
    static int               GET_LIFETIME_INTERVAL;
    static int               PLANT_ID;
    static String            PLANT_NAME;
    static int               PLANT_TIME_DAYS;

    static void load ( ) { }
    static void save ( ) { }
};

String            Configurations::WIFI_NAME                 = "A";
String            Configurations::WIFI_PASSWORD             = "A216191310";
// String            Configurations::WIFI_NAME                 = "Chacara Sao Jose";
// String            Configurations::WIFI_PASSWORD             = "020609031";
// String            Configurations::API_URL                   = "https://plantinha.herokuapp.com";
// String            Configurations::API_URL                   = "http://192.168.1.101:3306";
String            Configurations::API_URL                   = "http://192.168.15.7:3306";
long unsigned int Configurations::PUMP_CHECK_INTERVAL_MS    = 1000 * 5;
unsigned int      Configurations::PUMP_RUN_TIME_MS          = 1000 * 5;
int               Configurations::DRY_THRESHOLD_PERCENTAGE  = 5;
unsigned int      Configurations::DISPLAY_REFRESH_RATE      = 1000 * 5;
int               Configurations::GET_LIFETIME_INTERVAL     = 1000 * 5;
int               Configurations::PLANT_ID                  = 0;
String            Configurations::PLANT_NAME                = "????";
int               Configurations::PLANT_TIME_DAYS           = 0;