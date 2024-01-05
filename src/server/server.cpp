#include <stdio.h>
#include <ArduinoJson.h>

#include "auth.h"
#include "config.h"
#include "server.h"
#include "endpoints.h"


ESP8266WebServer server(HTTP_REST_PORT);


bool
server_authenticated()
{
#if defined(AUTH_USERNAME) && defined(AUTH_PASSWD)
    if(!server.authenticate(AUTH_USERNAME, AUTH_PASSWD)){
        server.requestAuthentication();
        return false;
    }
#endif
    return true;
}


void
server_config_routing() {
    server.on("/", HTTP_GET, get_root);

    server.on("/uptime", HTTP_GET, get_uptime);
    server.on("/uptime/json", HTTP_GET, get_uptime_json);

    server.on("/temperature", HTTP_GET, get_temperature);
    server.on("/temperature/json", HTTP_GET, get_temperature_json);

    server.onNotFound([]{server.send(404, "text/plain", "Not found");});

    char buf[16];
    const uint8_t pinMap[] = {D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10};
    for (int i=0; i<sizeof(pinMap); ++i) {
        uint8_t pin = pinMap[i];

        snprintf(buf, sizeof(buf), "/pin/D%d", i);
        server.on(buf, HTTP_GET,  [pin](){get_pin(pin);});
        server.on(buf, HTTP_POST, [pin](){post_pin(pin);});

        snprintf(buf, sizeof(buf), "/pin/D%d/toggle", i);
        server.on(buf, HTTP_POST, [pin](){post_pin_toggle(pin);});

        snprintf(buf, sizeof(buf), "/pin/D%d/mode", i);
        server.on(buf, HTTP_GET,  [pin](){get_pin_mode(pin);});
        server.on(buf, HTTP_POST, [pin](){post_pin_mode(pin);});
    }
}
