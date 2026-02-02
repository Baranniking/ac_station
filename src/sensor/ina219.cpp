#include "ina219.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

static Adafruit_INA219 ina219;
static float voltage = 0.0;
static float current = 0.0;
static float power = 0.0;
static bool fault = false;

bool ina219_init(void)
{
Wire.begin();
if(!ina219.begin()){
    return false;
}
ina219.setCalibraion_16V_100A();
}

void ina219_update(void)
{
    voltage = ina219_get_voltage();
    current = ina219_get_current();
    power = ina219_get_power();
}

float ina219_get_voltage(void)
{
    return voltage;
}

float ina219_get_current(void)
{
    return current;
}

float ina219_get_power(void)
{
    return power;
}

bool ina219_is_fault(void)
{
    return fault;
}
