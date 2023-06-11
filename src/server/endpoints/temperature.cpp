#include <stdio.h>
#include <ArduinoJson.h>

#include "restserver.h"
#include "sensors/temperature.h"


extern ESP8266WebServer server;


/**
 * @brief Perform a temperature measurement
 * 
 * GET
 *  
 */
void
get_temperature()
{
    float temperature = sensors_temperature_get();

    StaticJsonDocument<200> jsonDocument;
    jsonDocument["value"] = temperature;
    jsonDocument["updated"] = 0;

    char JSONmessageBuffer[50];
    serializeJsonPretty(jsonDocument, JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(202, "application/json", JSONmessageBuffer);
}
