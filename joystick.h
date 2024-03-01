#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IN_VOLTAGE2_RAW "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define IN_VOLTAGE3_RAW "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

char* file_reader(char* fileName);
int is_up();
int is_down();
int is_right();
int is_left();
void set_time();
int get_alm_hr();
int get_alm_min();

#endif