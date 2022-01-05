#pragma once
#include <FS.h>

class Database {
public:
    static String indexHtml;

    static void loadHtml ( ) {
        
    }

public:
    static void init ( ) {
        if(!SPIFFS.begin()){
            Serial.println("Failed to mount SPIFFS");
            return;
        }
        Serial.println("Database initialized");
    }

    // static String readFile ( const char * filename ) {
        
    // }

    static void printFile(const char * filename) {
        File file = SPIFFS.open(filename, "r");
        if (!file) {
            Serial.println("Failed to open file for reading");
            return;
        }
        while(file.available()){
            Serial.write(file.read());
        }
        file.close();
    }

    static void writeFile(const char * filename, const char * message) {
        
    }

    static String getHtml ( ) {
        return Database::indexHtml;
    }
};

String Database::indexHtml = "";