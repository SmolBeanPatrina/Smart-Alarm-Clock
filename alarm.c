#include "alarm.h"
#include "joystick.h"
#include "LEDMatrix.h"

int get_hourDiff()
{
    time_t T = time(NULL);
    struct tm currentTime = *localtime(&T);

    int alm_hr = get_alm_hr();

    int hourDiff = 0;

    if (alm_hr >= currentTime.tm_hour)
    {
        hourDiff = alm_hr - currentTime.tm_hour;
    }
    else
    {
        hourDiff = 23 - currentTime.tm_hour + alm_hr;

        if (currentTime.tm_min == 0)
        {
            hourDiff = hourDiff + 1;
        }
    }

    return hourDiff;
}

int get_minsDiff()
{
    time_t T = time(NULL);
    struct tm currentTime = *localtime(&T);

    int alm_min = get_alm_min();

    int minsDiff = 0;

    if (alm_min >= currentTime.tm_min)
    {
        minsDiff = alm_min - currentTime.tm_min;
    }
    else
    {
        minsDiff = 60 - currentTime.tm_min + alm_min;
    }

    return minsDiff;
}

int get_secsDiff()
{
    time_t T = time(NULL);
    struct tm currentTime = *localtime(&T);

    return currentTime.tm_sec;
}

long get_timeDiff_sec()
{
    int hourDiff = get_hourDiff();
    int minsDiff = get_minsDiff();
    int secsDiff = get_secsDiff();

    long timeDiff_sec = hourDiff * 60 * 60;
    timeDiff_sec = timeDiff_sec + (minsDiff * 60);
    timeDiff_sec = timeDiff_sec - secsDiff;

    return timeDiff_sec;
}

void buzz()
{
    runCommand("i2cset -y 1 0x70 0x83 0x01");
    runCommand("aplay wave-files/kurukuru.wav");
    sleep(3);
    // runCommand("i2cset -y 1 0x70 0x80 0x01");
}

void set_alarm()
{
    long alarmSet = get_timeDiff_sec();
    // printf("Sleep time: %ld", alarmSet);
    printf("Wait for alarm to buzz.\n\n");
    sleep(alarmSet);
    printf("~ Alarm Buzz ~\n\n");
    printf("Waiting for you to wake up.\n\n");


    buzz();

    // while()
}

void display()
{
    time_t T = time(NULL);
    struct tm currentTime = *localtime(&T);

    printf("System Date is: %02d/%02d/%04d\n", currentTime.tm_mday, currentTime.tm_mon + 1, currentTime.tm_year + 1900);
    printf("System Time is: %02d:%02d:%02d\n", currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
}
