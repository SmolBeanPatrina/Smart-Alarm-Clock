#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>
// #include <sys/ioctl.h>
// #include <linux/i2c.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <linux/i2c-dev.h>
// #include "joystick.h"

#include "LEDMatrix.h"
#include "joystick.h"
#include "alarm.h"
#include "lightSensor.h"

int main()
{
    printf("Welcome to bbg alarm!\n\n");
    disp_init();
    disp_default();

    set_time();
    set_alarm();
    is_roomlight_on();

    return 0;
}

// // Cycle through different hour and minute values to test the LED matrix
// for (int hour = 0; hour < 24; hour++) {
//     for (int minute = 0; minute < 60; minute++) {
//         // Display hour
//         DisInHour(hour);

//         // Wait for a bit before changing to minutes (adjust the sleep time as needed)
//         sleep(1);

//         // Display minute
//         DisInMin(minute);

//         // Wait for a bit before changing to next minute (adjust the sleep time as needed)
//         sleep(1);
//     }
// }