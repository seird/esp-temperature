Temperature sensor that periodically submits its measurements to a REST api. Can also be polled at `http://<ip>/sensor/temperature`.


## Wifi (+ basic auth) parameters in `include/auth.h`

```c
#ifndef __AUTH_H__
#define __AUTH_H__


#define WIFI_SSID "WifiSSID"
#define WIFI_PASSWD "WifiPassword"

/* Optionally use basic auth to authenticate to the esp */
#define AUTH_USERNAME "Username"
#define AUTH_PASSWD "Password"


#endif // __AUTH_H__
```
