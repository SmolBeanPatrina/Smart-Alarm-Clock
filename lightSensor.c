#include "lightSensor.h"
#include "joystick.h"
#include "LEDMatrix.h"

void is_roomlight_on()
{
    char *fileContent;
    int value = 0;
    
    printf("~ Sensing Light ~\n\n");
    while (value < 2000)
    {
        fileContent = file_reader(IN_VOLTAGE1_RAW);
        value = atoi(fileContent);
        runCommand("aplay wave-files/kurukuru.wav");
        // printf("Value: %d", value);
    }

    runCommand("i2cset -y 1 0x70 0x80 0x01");

    printf("\nGreat! You finally woke up.\n\n");
    runCommand("echo \"Good morning boss, I am coming to work\" | mail -s \"Greetings\" alexsyc97@gmail.com");
    // printf("Value: %d\n", value);
}