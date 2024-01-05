#include <stdio.h>
#include <ArduinoJson.h>

#include "server.h"


extern ESP8266WebServer server;


void
get_uptime_json()
{
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["value"] = millis()/1000;

    char JSONmessageBuffer[50];
    serializeJsonPretty(jsonDocument, JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}


void
get_uptime()
{
    unsigned long secondsSinceBoot = millis() / 1000;
    unsigned long days = secondsSinceBoot / (24*60*60);
    unsigned long hours = (secondsSinceBoot % (24*60*60)) / (60*60);
    unsigned long minutes = (secondsSinceBoot % (60*60)) / 60;
    unsigned long seconds = secondsSinceBoot % 60;

    char text[60];
    snprintf(text, sizeof(text), "%lud %2luh %2lum %2lus", days, hours, minutes, seconds);
    server.send(200, "text/plain", text);
}
