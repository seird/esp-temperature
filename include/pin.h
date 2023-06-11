#ifndef __PIN_H__
#define __PIN_H__


#include <stdint.h>


void pins_init();
void pin_set_mode(uint8_t id, uint8_t mode);
uint8_t pin_read_mode(uint8_t id);


#endif // __PIN_H__
