#include <stdio.h>

#include "restserver.h"


extern ESP8266WebServer server;


void
get_root()
{
    char message[100];
    sprintf(message, "%ld minutes since boot.", millis()/1000/60);
    server.send(200, "text/html", message);
}
