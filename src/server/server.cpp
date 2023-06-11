#include <stdio.h>
#include <ArduinoJson.h>

#include "auth.h"
#include "config.h"
#include "restserver.h"
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

    server.on("/pin/D0",  HTTP_GET, [](){get_pin(D0);});
    server.on("/pin/D1",  HTTP_GET, [](){get_pin(D1);});
    server.on("/pin/D2",  HTTP_GET, [](){get_pin(D2);});
    server.on("/pin/D3",  HTTP_GET, [](){get_pin(D3);});
    server.on("/pin/D4",  HTTP_GET, [](){get_pin(D4);});
    server.on("/pin/D5",  HTTP_GET, [](){get_pin(D5);});
    server.on("/pin/D6",  HTTP_GET, [](){get_pin(D6);});
    server.on("/pin/D7",  HTTP_GET, [](){get_pin(D7);});
    server.on("/pin/D8",  HTTP_GET, [](){get_pin(D8);});
    server.on("/pin/D9",  HTTP_GET, [](){get_pin(D9);});
    server.on("/pin/D10", HTTP_GET, [](){get_pin(D10);});

    server.on("/pin/D0",  HTTP_POST, [](){post_pin(D0);});
    server.on("/pin/D1",  HTTP_POST, [](){post_pin(D1);});
    server.on("/pin/D2",  HTTP_POST, [](){post_pin(D2);});
    server.on("/pin/D3",  HTTP_POST, [](){post_pin(D3);});
    server.on("/pin/D4",  HTTP_POST, [](){post_pin(D4);});
    server.on("/pin/D5",  HTTP_POST, [](){post_pin(D5);});
    server.on("/pin/D6",  HTTP_POST, [](){post_pin(D6);});
    server.on("/pin/D7",  HTTP_POST, [](){post_pin(D7);});
    server.on("/pin/D8",  HTTP_POST, [](){post_pin(D8);});
    server.on("/pin/D9",  HTTP_POST, [](){post_pin(D9);});
    server.on("/pin/D10", HTTP_POST, [](){post_pin(D10);});

    server.on("/pin/D0/toggle",  HTTP_POST, [](){post_pin_toggle(D0);});
    server.on("/pin/D1/toggle",  HTTP_POST, [](){post_pin_toggle(D1);});
    server.on("/pin/D2/toggle",  HTTP_POST, [](){post_pin_toggle(D2);});
    server.on("/pin/D3/toggle",  HTTP_POST, [](){post_pin_toggle(D3);});
    server.on("/pin/D4/toggle",  HTTP_POST, [](){post_pin_toggle(D4);});
    server.on("/pin/D5/toggle",  HTTP_POST, [](){post_pin_toggle(D5);});
    server.on("/pin/D6/toggle",  HTTP_POST, [](){post_pin_toggle(D6);});
    server.on("/pin/D7/toggle",  HTTP_POST, [](){post_pin_toggle(D7);});
    server.on("/pin/D8/toggle",  HTTP_POST, [](){post_pin_toggle(D8);});
    server.on("/pin/D9/toggle",  HTTP_POST, [](){post_pin_toggle(D9);});
    server.on("/pin/D10/toggle", HTTP_POST, [](){post_pin_toggle(D10);});

    server.on("/pin/D0/mode",  HTTP_GET, [](){get_pin_mode(D0);});
    server.on("/pin/D1/mode",  HTTP_GET, [](){get_pin_mode(D1);});
    server.on("/pin/D2/mode",  HTTP_GET, [](){get_pin_mode(D2);});
    server.on("/pin/D3/mode",  HTTP_GET, [](){get_pin_mode(D3);});
    server.on("/pin/D4/mode",  HTTP_GET, [](){get_pin_mode(D4);});
    server.on("/pin/D5/mode",  HTTP_GET, [](){get_pin_mode(D5);});
    server.on("/pin/D6/mode",  HTTP_GET, [](){get_pin_mode(D6);});
    server.on("/pin/D7/mode",  HTTP_GET, [](){get_pin_mode(D7);});
    server.on("/pin/D8/mode",  HTTP_GET, [](){get_pin_mode(D8);});
    server.on("/pin/D9/mode",  HTTP_GET, [](){get_pin_mode(D9);});
    server.on("/pin/D10/mode", HTTP_GET, [](){get_pin_mode(D10);});

    server.on("/pin/D0/mode",  HTTP_POST, [](){post_pin_mode(D0);});
    server.on("/pin/D1/mode",  HTTP_POST, [](){post_pin_mode(D1);});
    server.on("/pin/D2/mode",  HTTP_POST, [](){post_pin_mode(D2);});
    server.on("/pin/D3/mode",  HTTP_POST, [](){post_pin_mode(D3);});
    server.on("/pin/D4/mode",  HTTP_POST, [](){post_pin_mode(D4);});
    server.on("/pin/D5/mode",  HTTP_POST, [](){post_pin_mode(D5);});
    server.on("/pin/D6/mode",  HTTP_POST, [](){post_pin_mode(D6);});
    server.on("/pin/D7/mode",  HTTP_POST, [](){post_pin_mode(D7);});
    server.on("/pin/D8/mode",  HTTP_POST, [](){post_pin_mode(D8);});
    server.on("/pin/D9/mode",  HTTP_POST, [](){post_pin_mode(D9);});
    server.on("/pin/D10/mode", HTTP_POST, [](){post_pin_mode(D10);});

    server.on("/sensor/temperature", HTTP_GET, get_temperature);
}
