#ifndef __ENDPOINTS_H__
#define __ENDPOINTS_H__


#include <stdint.h>


void get_pin(uint8_t id);
void post_pin(uint8_t id);
void post_pin_toggle(uint8_t id);

void get_pin_mode(uint8_t id);
void post_pin_mode(uint8_t id);

void get_root();

void get_uptime();
void get_uptime_json();

void get_temperature();
void get_temperature_json();

#endif // __ENDPOINTS_H__
