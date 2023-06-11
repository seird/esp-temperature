#include <Arduino.h>
#include "pin.h"


struct Pin {
    uint8_t id;
    uint8_t mode;
};

// D4 is also LED_BUILTIN (on when pin is low)

static const uint8_t gpio_ids[] = {D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10};
static struct Pin pins[sizeof(gpio_ids)];


void
pins_init()
{
    for (size_t i=0; i<sizeof(gpio_ids); ++i) {
        pinMode(gpio_ids[i], OUTPUT);
        pins[i].id = gpio_ids[i];
        pins[i].mode = OUTPUT;
    }
    // set D4 pin to HIGH to turn off the LED by default
    digitalWrite(D4, HIGH);
}


void
pin_set_mode(uint8_t id, uint8_t mode)
{
    pinMode(id, mode);
    for (size_t i=0; i<sizeof(gpio_ids); ++i) {
        if (id == pins[i].id) {
            pins[i].mode = mode;
            return;
        }
    }
}


uint8_t
pin_read_mode(uint8_t id)
{
    for (size_t i=0; i<sizeof(gpio_ids); ++i) {
        if (id == pins[i].id) {
            return pins[i].mode;
        }
    }
    return 3;
}
