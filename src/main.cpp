#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#include "auth.h"
#include "config.h"
#include "pin.h"
#include "server.h"
#include "sensors/temperature.h"


extern ESP8266WebServer server;


#if defined(URL_SUBMIT) && defined(SENSOR_ID) && defined(SUBMIT_EVERY_MS)
static unsigned long last_submit = 0;
#endif


int
init_wifi()
{
    digitalWrite(D4, LOW);

    WiFi.mode(WIFI_STA);
#ifdef HOSTNAME
    WiFi.setHostname(HOSTNAME);
#endif
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
    sensors_temperature_init(PIN_SENSOR_DATA);
    init_wifi();

    server_config_routing();
    server.begin();
}


#if defined(URL_SUBMIT) && defined(SENSOR_ID) && defined(SUBMIT_EVERY_MS)
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
#endif


void
loop(void)
{
    if (WiFi.status() != WL_CONNECTED) {
        init_wifi();
    }

#if defined(URL_SUBMIT) && defined(SENSOR_ID) && defined(SUBMIT_EVERY_MS)
    // due to lack of transparent bridge mode, submit to the server periodically
    if (millis() > (last_submit + SUBMIT_EVERY_MS)) {
        send_temperature();
        last_submit = millis();
    }
#endif

    server.handleClient();
}
