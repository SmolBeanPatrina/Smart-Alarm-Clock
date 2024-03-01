#include "LEDMatrix.h"


typedef struct {
    unsigned char address_row;
    int row_hex_value;
} number;

number num_array[MAX_DIGIT][DISPLAY_SIZE] = {
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x20},{REG_DIR3, 0x50},{REG_DIR4, 0x50},{REG_DIR5, 0x50},{REG_DIR6, 0x50},{REG_DIR7, 0x50},{REG_DIR8, 0x20}, },  // num0
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x70},{REG_DIR3, 0x20},{REG_DIR4, 0x20},{REG_DIR5, 0x20},{REG_DIR6, 0x20},{REG_DIR7, 0x60},{REG_DIR8, 0x20}, },  // num1 
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x70},{REG_DIR3, 0x40},{REG_DIR4, 0x20},{REG_DIR5, 0x10},{REG_DIR6, 0x10},{REG_DIR7, 0x50},{REG_DIR8, 0x20}, },  // num2
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x20},{REG_DIR3, 0x50},{REG_DIR4, 0x10},{REG_DIR5, 0x20},{REG_DIR6, 0x10},{REG_DIR7, 0x50},{REG_DIR8, 0x20}, },  // num3
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x10},{REG_DIR3, 0x10},{REG_DIR4, 0x10},{REG_DIR5, 0x70},{REG_DIR6, 0x50},{REG_DIR7, 0x50},{REG_DIR8, 0x50}, },  // num4
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x70},{REG_DIR3, 0x50},{REG_DIR4, 0x10},{REG_DIR5, 0x70},{REG_DIR6, 0x40},{REG_DIR7, 0x50},{REG_DIR8, 0x70}, },  // num5
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x20},{REG_DIR3, 0x50},{REG_DIR4, 0x50},{REG_DIR5, 0x60},{REG_DIR6, 0x40},{REG_DIR7, 0x20},{REG_DIR8, 0x10}, },  // num6
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x10},{REG_DIR3, 0x10},{REG_DIR4, 0x10},{REG_DIR5, 0x38},{REG_DIR6, 0x10},{REG_DIR7, 0x10},{REG_DIR8, 0x70}, },  // num7
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x20},{REG_DIR3, 0x50},{REG_DIR4, 0x50},{REG_DIR5, 0x20},{REG_DIR6, 0x50},{REG_DIR7, 0x50},{REG_DIR8, 0x20}, },  // num8
    {{REG_DIR1, 0x00}, {REG_DIR2, 0x10},{REG_DIR3, 0x10},{REG_DIR4, 0x10},{REG_DIR5, 0x70},{REG_DIR6, 0x50},{REG_DIR7, 0x50},{REG_DIR8, 0x20}, },  // num9

};

int initI2cBus(char *bus, int address) {
    int i2cFileDesc = open(bus, O_RDWR);
    if (i2cFileDesc < 0 || ioctl(i2cFileDesc, I2C_SLAVE, address) < 0) {
        perror("I2C: Unable to initialize bus");
        exit(1);
    }
    return i2cFileDesc;
}

void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value) {
    unsigned char buff[2] = {regAddr, value};
    if (write(i2cFileDesc, buff, 2) != 2) {
        perror("I2C: Unable to write to register");
        exit(1);
    }
}

void runCommand(char *command)
{
    FILE *pipe = popen(command, "r");
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe))
    {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
    }
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0)
    {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

void disp_init() {
    runCommand("config-pin P9_18 i2c");
    runCommand("config-pin P9_17 i2c");
    runCommand("i2cset -y 1 0x70 0x21 0x00");
    runCommand("i2cset -y 1 0x70 0x81 0x00");
}

void disp_default()
{
    runCommand("i2cset -y 1 0x70 0x00 0xff");
    runCommand("i2cset -y 1 0x70 0x0e 0xff");
    runCommand("i2cset -y 1 0x70 0x02 0xc0");
    runCommand("i2cset -y 1 0x70 0x04 0xc0");
    runCommand("i2cset -y 1 0x70 0x06 0xc0");
    runCommand("i2cset -y 1 0x70 0x08 0xc0");
    runCommand("i2cset -y 1 0x70 0x0a 0xc0");
    runCommand("i2cset -y 1 0x70 0x0c 0xc0");
}

void DisNum(int i2cFileDesc, int digit1, int digit2) {
    for (int i = 0; i < DISPLAY_SIZE; i++) {
        number n = num_array[digit1][i];
        n.row_hex_value += shift(num_array[digit2][i].row_hex_value);
        writeI2cReg(i2cFileDesc, n.address_row, n.row_hex_value);
    }
}
void DisInHour(int value) {
    if (value > 10000) {
        printf("Value too high, please restart it.\n");
        return;
    }
    // Adjust value for 24-hour format
    value = value % 24;

    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
    int digit1 = value / 10;
    int digit2 = value % 10; 

    DisNum(i2cFileDesc, digit1, digit2);
    close(i2cFileDesc);

    
}
void DisInMin(int value) {
    if (value > 10000) {
        printf("Value too high, please restart it.\n");
        return;
    }
    // Adjust value for 60-minute format
    value = value % 60;

    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
    int digit1 = value / 10; 
    int digit2 = value % 10; 

    DisNum(i2cFileDesc, digit1, digit2);
    close(i2cFileDesc);
}