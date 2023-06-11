#include <stdio.h>
#include <ArduinoJson.h>

#include "restserver.h"


extern ESP8266WebServer server;


void
get_uptime()
{
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["uptime"] = millis()/1000;

    char JSONmessageBuffer[50];
    serializeJsonPretty(jsonDocument, JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}
