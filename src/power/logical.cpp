#include "logical.h"
#include <config.h>
#include <Arduino.h>
#include "bms_manager.h"
//внутренее состояние, не видно из вне.
static charger_state state = CHARGER_OFF;
static bool checkResMillis = false;
static bool activCharge = false;
static uint32_t chargeStartTime = 0;
static uint16_t stateBatt = 0;
static SystemState systemState;


void charger_init(void)
{
    pinMode(CHARGER_EN_PIN, OUTPUT); 
    digitalWrite(CHARGER_EN_PIN, HIGH); 
    state = CHARGER_OFF;
}

void logicalUpdate(){
const DataBMS bms = bms_get_data();
systemState.soc = bms.batProcent;
systemState.voltage = bms.batVolatge;
systemState.current = bms.batCurrent;
systemState.temp = bms.batTemp;
systemState.chargeEnabled = bms.getChargeState;
systemState.dischargeEnabled = bms.getDischargeState;
}


const SystemState* logic_get_state()
{
    return &systemState;
}

 void charger_logical(void)
{
      switch(state)
    {
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


/////
charger_state charger_get_state(void)
{
    return state;
}

/////
void charger_set_state(charger_state newState)
{
state = newState;
}


void activSetChargAU(bool state){
    activCharge = state;
}






void charger_enable(void)
{
    uint32_t delayTimeOnChargeBms = 5000;
    
    if(activCharge) return;

    if(!checkResMillis){
    digitalWrite(CHARGER_EN_PIN, LOW); //включение блока питания
    checkResMillis = true;
    chargeStartTime = millis();
    }

    if(checkResMillis && millis() - chargeStartTime >= delayTimeOnChargeBms){
        bmsPtr->setChargeMOS(true);
        Serial.println("onMOScharge");
        checkResMillis = false;
        activCharge = true;
        
    }
}

void charger_disable(void)
{
    if(!activCharge) return;
    digitalWrite(CHARGER_EN_PIN, HIGH);
    bmsPtr->setChargeMOS(false);
    Serial.println("offMOScharge");
       checkResMillis = false;
       activCharge = false;
}

void charger_au(void)
{
    stateBatt = bmsPtr->get.packSOC;
    if(!activCharge && stateBatt <= START_CHARG){
        charger_enable();


    }else if(activCharge && stateBatt >= STOP_CHARG)
    {
        charger_disable();
        
    }
}

 
