#pragma once
#include <Arduino.h>

void bms_manager_init(HardwareSerial& serial);
void bms_manager_update();

float bms_get_soc();
float bms_get_bat_voltage();
float bms_get_current();
float bms_get_temp();

bool bms_get_charge();
bool bms_get_discharge();

void bms_set_charge(bool state);
void bms_set_discharge(bool state);
