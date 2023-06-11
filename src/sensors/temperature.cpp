#include <OneWire.h>
#include <DS18B20.h>
#include "config.h"


static OneWire oneWire(PIN_SENSOR_DATA);
static DS18B20 sensorTemp(&oneWire);


void
sensors_temperature_init()
{
    while (!sensorTemp.begin()) {
        for (int i=0; i<10; ++i) {
            digitalWrite(D4, LOW);
            delay(100);
            digitalWrite(D4, HIGH);
            delay(100);
        }
    }

    sensorTemp.setResolution(12);
}


float
sensors_temperature_get()
{
    sensorTemp.requestTemperatures();
    while (!sensorTemp.isConversionComplete());  // wait until sensor is ready
    return sensorTemp.getTempC();
}
