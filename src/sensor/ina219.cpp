#include "ina219.h"
#include <Adafruit_INA219.h>


static float voltage = 13.5;
static float current = 2.1;
static bool fault = false;

bool ina219_init(void)
{
    return true;
}

void ina219_update(void)
{
    // позже тут будет чтение I2C
}

float ina219_get_voltage(void)
{
    return voltage;
}

float ina219_get_current(void)
{
    return current;
}

bool ina219_is_fault(void)
{
    return fault;
}
