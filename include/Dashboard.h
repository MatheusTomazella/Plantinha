#pragma once
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHTesp.h>
#include <HumiditySensor.h>
#include <Reservoir.h>
 
WiFiClient client;
HTTPClient http;

class Dashboard {
public:
    DHTesp* dht;
    HumiditySensor* hSensor;
    Reservoir* reservoir;
    
    Dashboard ( DHTesp* dht, HumiditySensor* hSensor, Reservoir* reservoir ) {
        this->dht = dht;
        this->hSensor = hSensor;
        this->reservoir = reservoir;
	}

    bool connect ( String route = "" ) {
        return http.begin( client, Configurations::API_URL + route );
    }

    void disconnect ( ) {
        http.end();
    }

    void postData ( ) {
        if ( !connect("/plant/data/" + String( Configurations::PLANT_ID )) ) {
            Serial.println( "Failed to connect to server" );
            Serial.println( http.getString() );
            return;
        }

        TempAndHumidity dhtReadings = dht->getTempAndHumidity();
        float temp = dhtReadings.temperature;
        float hum = dhtReadings.humidity;
        int lifeTime = Configurations::PLANT_TIME_DAYS;
        int soilHumidity = hSensor->getPercentage();
        int waterLevel = reservoir->getLevelPercentage();
        String data = "{\"temperature\":"+String(temp)+",\"airHumidity\":"+String(hum)+",\"lifeTime\":"+String(lifeTime)+",\"soilHumidity\":"+String(soilHumidity)+",\"waterLevel\":"+String(waterLevel)+"}";

        http.addHeader( "Content-Type", "application/json" );
        if ( http.POST( data ) != 200 ) {
            Serial.println( "Failed to send data to server" );
            Serial.println( http.getString() );
            return;
        } else {
            // Serial.println( "Data sent to server" );
        }

        disconnect();
    }

    void loadLifetime ( ) {
        if ( !connect("/plant/data/lifetime/" + String( Configurations::PLANT_ID )) ) {
            Serial.println( "Failed to connect to server" );
            return;
        }

        if ( http.GET() != 200 ) {
            Serial.println( "Failed to get lifetime from server" );
            Serial.println( http.getString() );
            return;
        }

        String response = http.getString();
        int lifetime = response.toInt();
        Configurations::PLANT_TIME_DAYS = lifetime;

        disconnect();
    }

    void loadName ( ) {
        if ( !connect("/plant/name/" + String( Configurations::PLANT_ID )) ) {
            Serial.println( "Failed to connect to server" );
            return;
        }

        if ( http.GET() != 200 ) {
            Serial.println( "Failed to get name from server" );
            Serial.println( http.getString() );
            return;
        }

        String response = http.getString();
        Configurations::PLANT_NAME = response;

        disconnect();
    }

private:

    
};