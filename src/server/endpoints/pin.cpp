#include <stdio.h>
#include <ArduinoJson.h>
#include <Ticker.h>

#include "config.h"
#include "pin.h"
#include "restserver.h"


extern ESP8266WebServer server;


Ticker toggler;


void
get_pin(uint8_t id)
{
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["value"] = digitalRead(id);

    char JSONmessageBuffer[50];
    serializeJsonPretty(jsonDocument, JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}


void
post_pin(uint8_t id)
{
    if (!server_authenticated()) {
        return;
    }

    StaticJsonDocument<500> jsonDocument;
    DeserializationError error = deserializeJson(jsonDocument, server.arg("plain"));

    if (error) {
        server.send(400);
        return;
    }

    if (!jsonDocument.containsKey("value")) {
        server.send(400);
        return;
    }

    if (pin_read_mode(id) != OUTPUT) {
        // can only write a value to OUTPUT pins
        server.send(400);
        return;
    }

    digitalWrite(id, jsonDocument["value"]);

    if (jsonDocument.containsKey("duration") && jsonDocument["duration"] > 0) {
        uint8_t value = jsonDocument["value"];
        toggler.attach_ms(
            jsonDocument["duration"],
            [id, value](){
                digitalWrite(id, !value);
                toggler.detach();
            }
        );
    }

    server.send(202);
}


void
post_pin_toggle(uint8_t id)
{
    if (!server_authenticated()) {
        return;
    }

    if (pin_read_mode(id) != OUTPUT) {
        // can only write a value to OUTPUT pins
        server.send(400);
        return;
    }

    digitalWrite(id, !digitalRead(id));

    server.send(202);
}


void
get_pin_mode(uint8_t id)
{
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["mode"] = pin_read_mode(id);

    char JSONmessageBuffer[50];
    serializeJsonPretty(jsonDocument, JSONmessageBuffer, sizeof(JSONmessageBuffer));
    server.send(200, "application/json", JSONmessageBuffer);
}


void
post_pin_mode(uint8_t id)
{
    if (!server_authenticated()) {
        return;
    }

    StaticJsonDocument<500> jsonDocument;
    DeserializationError error = deserializeJson(jsonDocument, server.arg("plain"));

    if (error) {
        server.send(400);
        return;
    }

    if (!jsonDocument.containsKey("mode")) {
        server.send(400);
        return;
    }

    pin_set_mode(id, jsonDocument["mode"]);

    server.send(202);
}
