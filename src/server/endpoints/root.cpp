#include <stdio.h>

#include "server.h"
#include "sensors/temperature.h"


extern ESP8266WebServer server;


void
get_root()
{
    char html[1024];
    snprintf(html, sizeof(html),
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
           "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
            "<style>"
                "body { font-family: Arial, sans-serif; text-align: center; margin: 5vw auto; max-width: 80%%; }"
                ".temperature { font-size: 15vw; display: inline-block; color: #1c1b22; }"
                "@media (prefers-color-scheme: dark) {"
                    "body { background-color: #1c1b22; color: #eee; }"
                    ".temperature { color: lightgray; }"  // Adjusted color for dark mode
                "}"
            "</style>"
        "</head>"
        "<body>"
            "<p class='temperature'>%2.1f&deg;C</p>"
        "</body>"
        "</html>",
        sensors_temperature_get()
    );

    server.send(200, "text/html", html);
}
