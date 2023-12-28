#include <stdio.h>
#include <ArduinoJson.h>

#include "server.h"
#include "sensors/temperature.h"


extern ESP8266WebServer server;


void
get_temperature_json()
{
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["value"] = sensors_temperature_get();

    char JSONmessageBuffer[50];
    serializeJsonPretty(jsonDocument, JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}


void
get_temperature()
{
    char text[20];
    snprintf(text, sizeof(text), "%.2f", sensors_temperature_get());
    server.send(200, "text/plain", text);
}
