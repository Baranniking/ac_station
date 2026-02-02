#ifndef INA219_SENSOR_H
#define INA219_SENSOR_H

#include <stdint.h>
#include <stdbool.h>

//инициализация датчика
bool ina219_init(void);

//обовления показания датчика
void ina219_update(void);

//получаем напряжение акб
float ina219_get_voltage(void);

//получаем ток зарядки
float ina219_get_current(void);

// флаг ошибки датчика
bool ina219_is_fault(void);

#endif