#ifndef _LEDS_H_
#define _LEDS_H_
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define DISPLAY_SIZE 8
#define MAX_DIGIT 10
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stddef.h>

#define I2C_DEVICE_ADDRESS 0x70
#define REG_DIR1 0x00
#define REG_DIR2 0x02
#define REG_DIR3 0x04
#define REG_DIR4 0x06
#define REG_DIR5 0x08
#define REG_DIR6 0x0A
#define REG_DIR7 0x0C
#define REG_DIR8 0x0E
#define REG_OUTA 0x14
#define REG_OUTB 0x15
#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"
#define LED_ROWS 8
#define shift(a) (a >> 4)

void runCommand(char *command);
void disp_init();
void disp_default();
int initI2cBus(char *bus, int address);
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);
void DisInHour(int value);
void DisInMin(int value);
//void DisIntTime(int hours, int minutes)
#endif