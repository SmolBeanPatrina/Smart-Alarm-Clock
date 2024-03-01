#ifndef _LIGHTSENSOR_H_
#define _LIGHTSENSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_VOLTAGE1_RAW "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"

void is_roomlight_on();
#endif