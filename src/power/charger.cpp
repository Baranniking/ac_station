#include "charger.h"
#include <Arduino.h>
#include "config.h"
#include "ina219.h"

//внутренее состояние, не видно из вне.
static charger_state state = CHARGER_OFF;



charger_state charger_get_state(void)
{
    return state;
}

void charger_set_state(charger_state newState)
{
state = newState;
}


// публичные функции 

void charger_init(void)
{
    pinMode(CHARGER_EN_PIN, OUTPUT); 
    digitalWrite(CHARGER_EN_PIN, LOW); 
    state = CHARGER_OFF;
}

void charger_enable(void)
{
    digitalWrite(CHARGER_EN_PIN, HIGH);
}

void charger_disable(void)
{
    digitalWrite(CHARGER_EN_PIN, LOW);
}

void charger_au(void)
{
      
      float v = ina219_get_voltage();
      float i = ina219_get_current();

    if(v <= VOLTAGE_START_CHARGE){
            charger_enable();
        }
        if(v >= CHARGE_VOLTAGE_MAX){
            charger_disable();
            state = CHARGER_DONE; 
        }
}

void charger_fault(void){
    digitalWrite(CHARGER_EN_PIN, LOW);
    //ошибку на дисплей

}

    //////////////////////////////////////////////////////////////////////// логика зарядки
    void charger_logical(void)
{
      switch(state)
    {
        ina219_update();
        case CHARGER_ON:
        charger_enable();
        break;

        case CHARGER_OFF:
        charger_disable();
        break;

        case CHARGER_AUTO:
        charger_au();
        break;

        case CHARGER_DONE:
        charger_disable();
        // запуск функции оповищение на дисплей
        break;
        
        case CHARGER_FAULT:
        charger_disable(); 
        //запуск фунеции ошибки на дисплей
        break;

        

        
    }
}
