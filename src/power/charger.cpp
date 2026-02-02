#include <Arduino.h>
#include "charger.h"
#include "config.h"

//внутренее состояние, не видно из вне.
static charger_state state = CHARGER_OFF;


//вводные данные для зарядки
static float battery_voltage = 13.2;
static uint8_t charger_current = 30;
static uint8_t battery_temp = 25;

// публичные функции 

void charger_init(void)
{
    pinMode(CHARGER_EN_PIN, OUTPUT); //Пин на выход
    digitalWrite(CHARGER_EN_PIN, LOW); // пин опущен
    state = CHARGER_OFF;
}

void charger_enable(void)
{
    digitalWrite(CHARGER_EN_PIN, HIGH); //Включаем зарядку
    state = CHARGER_ON;
}

void charger_disable(void)
{
    digitalWrite(CHARGER_EN_PIN, LOW);
    state = CHARGER_OFF;
}

void charger_au(void){
    // логика работы в авто режиме
    state  = CHARGER_AUTO;
}

charger_state charger_get_state(void){
    return state;
}

    // логика зарядки
void charger_logical(void)
{
    switch(state)
    {
        case CHARGER_OFF:
        digitalWrite(CHARGER_EN_PIN, LOW);
        
        break;

        case CHARGER_CHECK:
            if(battery_voltage >= CHARGE_VOLTAGE_MAX){
                state = CHARGER_DONE;
                break;
            }
            if(battery_temp >= BATTERY_TEMP_MAX){
                state = CHARGER_FAULT;
                break;
            }
            break;
        
        case CHARGER_DONE:
        digitalWrite(CHARGER_EN_PIN, LOW);
        // оповищение на дисплей
        break;
        
        case CHARGER_FAULT:
        digitalWrite(CHARGER_EN_PIN, LOW);
        
        //ошибку на дисплей
        break;

        case CHARGER_ON:
        digitalWrite(CHARGER_EN_PIN, HIGH);
       
        break;

        case CHARGER_AUTO:
        if(battery_voltage <= VOLTAGE_START_CHARGE){
            digitalWrite(CHARGER_EN_PIN, HIGH);
            break;
        }
        if(battery_voltage >= CHARGE_VOLTAGE_MAX){
            digitalWrite(CHARGER_EN_PIN, LOW);
         break;   
        }
        if(battery_temp >= BATTERY_TEMP_MAX){
            digitalWrite(CHARGER_EN_PIN, LOW);
            state = CHARGER_FAULT;

        }
        break;
    }
}
