#include "joystick.h"
#include "LEDMatrix.h"

struct time
{
    int hr;
    int min;
};

struct time alm;

char *file_reader(char *fileName)
{
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("ERROR OPENING: %s\n", fileName);
        fclose(file);
        return NULL;
    }

    char buffer[100];
    fgets(buffer, 100, file);
    fclose(file);

    char *fileContent = strdup(buffer);
    return fileContent;
}

int is_up()
{
    char *fileContent = file_reader(IN_VOLTAGE2_RAW);
    int value = atoi(fileContent);

    if (value < 500)
    {
        return 1;
    }

    return 0;
}

int is_down()
{
    char *fileContent = file_reader(IN_VOLTAGE2_RAW);
    int value = atoi(fileContent);

    if (value > 3500)
    {
        return 1;
    }

    return 0;
}

int is_right()
{
    char *fileContent = file_reader(IN_VOLTAGE3_RAW);
    int value = atoi(fileContent);

    if (value < 500)
    {
        return 1;
    }

    return 0;
}

int is_left()
{
    char *fileContent = file_reader(IN_VOLTAGE3_RAW);
    int value = atoi(fileContent);

    if (value > 3500)
    {
        return 1;
    }

    return 0;
}

void set_time()
{
    printf("Enter: joystick-right\n\n");
    while (!is_right())
    {
    }

    if (is_right())
    {
        printf("~ Set Hour ~ \n");
        printf("Browse: joystick-up/down\n");
        printf("Enter: joystick-right\n");
        DisInHour(0);
    }

    while (!is_up())
    {
        if (is_down())
        {
            break;
        }
    }

    int hour = 0;

    do
    {
        while (!is_up())
        {
            if (is_down())
            {
                break;
            }
            else if (is_right())
            {
                printf("Done!\n\n");
                alm.hr = hour;
                goto SetMinutes;
            }
        }

        if (is_up())
        {
            if (hour == 23)
            {
                hour = -1;
            }
            hour = hour + 1;
            DisInHour(hour);
        }
        else if (is_down())
        {
            if (hour == 0)
            {
                hour = 24;
            }
            hour = hour - 1;
            DisInHour(hour);
        }

        while (is_up() || is_down())
        {
        }

    } while (!is_right());

SetMinutes:
    printf("~ Set Minutes ~\n");
    int mins = 0;
    DisInMin(mins);

    while (!is_up())
    {
        if (is_down())
        {
            break;
        }
    }

    do
    {
        while (!is_up())
        {
            if (is_down())
            {
                break;
            }
            else if (is_right())
            {
                printf("Done!\n\n");
                alm.min = mins;
                goto TimeSet;
            }
        }

        if (is_up())
        {
            if (mins == 59)
            {
                mins = -1;
            }
            mins = mins + 1;
            DisInMin(mins);
        }
        else if (is_down())
        {
            if (mins == 0)
            {
                mins = 60;
            }
            mins = mins - 1;
            DisInMin(mins);
        }

        while (is_up() || is_down())
        {
        }

    } while (!is_right());

TimeSet:
    printf("~ Time Set ~\n");
    printf("Done!\n\n");
    disp_default();
}

int get_alm_hr()
{
    return alm.hr;
}

int get_alm_min()
{
    return alm.min;
}