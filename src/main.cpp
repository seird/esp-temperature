#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#include "auth.h"
#include "config.h"
#include "pin.h"
#include "restserver.h"
#include "sensors/temperature.h"


extern ESP8266WebServer server;
static unsigned long last_submit = 0;


int
init_wifi()
{
    digitalWrite(D4, LOW);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(WIFI_RETRY_DELAY);
    }

    digitalWrite(D4, HIGH);
    
    return WiFi.status();
}


void
setup(void)
{
    Serial.begin(9600);

    pins_init();
    sensors_temperature_init();
    init_wifi();

    server_config_routing();
    server.begin();
}


void
send_temperature()
{
    HTTPClient http;
    WiFiClient wificlient;

    // Build the json string
    StaticJsonDocument<200> jsonDocument;
    char JSONmessageBuffer[50];
    jsonDocument["id"] = SENSOR_ID;
    jsonDocument["value"] = sensors_temperature_get();
    serializeJsonPretty(jsonDocument, JSONmessageBuffer, sizeof(JSONmessageBuffer));

    // Make the POST request
    http.begin(wificlient, URL_SUBMIT);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-ACCESS-TOKEN", APIKEY);
    http.POST(JSONmessageBuffer);
    http.end();
}


void
loop(void)
{
    if (WiFi.status() != WL_CONNECTED) {
        init_wifi();
    }

    // due to lack of transparent bridge mode, submit to the server periodically
    if (millis() > (last_submit + SUBMIT_EVERY_MS)) {
        send_temperature();
        last_submit = millis();
    }

    server.handleClient();
}
