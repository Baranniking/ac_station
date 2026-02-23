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

void logicalUpdateDataBMS(){
const DataBMS bms = bms_get_data();
bms_manager_update();   // <-- добавить сюда
systemState.soc = bms.batProcent;
systemState.voltage = bms.batVolatge;
systemState.current = bms.batCurrent;
systemState.temp = bms.batTemp;
systemState.chargeEnabled = bms.getChargeState;
systemState.dischargeEnabled = bms.getDischargeState;
}


const SystemState* logical_get()
{
    return &systemState;
}

////////////////////////////////////////////////////////////////////////////////////////////

 void charger_logical(void)
{
      switch(state)
    {
        case CHARGER_ON:
        logical_charger_enable();
        break;

        case CHARGER_OFF:
        logical_charger_disable();
        break;

        case CHARGER_AUTO:
        logical_toggle_auto_mode();
        break;

        case CHARGER_DONE:
        logical_charger_disable();
        break;
        
        case CHARGER_FAULT:
        logical_charger_disable(); 
        break;        
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

void logical_charger_enable(void)
{
    static const uint32_t delayTimeOnChargeBms = 5000;
    
    if(activCharge) return;

    if(!checkResMillis){
    digitalWrite(CHARGER_EN_PIN, LOW); //включение блока питания
    checkResMillis = true;
    chargeStartTime = millis();
    }

    if(checkResMillis && millis() - chargeStartTime >= delayTimeOnChargeBms){
        bms_set_charge(true);
        Serial.println("onMOScharge");
        checkResMillis = false;
        activCharge = true;
        
    }
}

void logical_charger_disable(void)
{
    if(!activCharge) return;
    digitalWrite(CHARGER_EN_PIN, HIGH);
    bms_set_charge(false);
    Serial.println("offMOScharge");
       checkResMillis = false;
       activCharge = false;
}

void logical_toggle_auto_mode(void)
{
   if(systemState.temp > MAX_TEMP){
     state = CHARGER_FAULT;
     return;
   }
   if(systemState.soc <= START_CHARG){
    logical_charger_enable();
   }else if(systemState.soc >= 100 && systemState.current <= 5){
    logical_charger_disable();
    state = CHARGER_DONE;
   }
        
    }


/////
charger_state logical_get_state(void)
{
    return state;
}

/////
void logical_set_state(charger_state newState)
{
state = newState;
}


void activSetChargAU(bool state){
    activCharge = state;
}












 
