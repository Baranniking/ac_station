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
    fault = true;
    return false;
}
ina219.setCalibration_16V_400mA();
    fault = false;
    return true;
}

void ina219_update(void)
{
 if (!ina219.success()) {
        fault = true;
        return;
    }

    voltage = ina219.getBusVoltage_V();
    current = ina219.getCurrent_mA();
    power = ina219.getPower_mW();

    fault = false;
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
