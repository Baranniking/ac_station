#include "bms_manager.h"
#include <daly-bms-uart.h>

static Daly_BMS_UART bms(Serial1); //создаем обьект бмс

  

struct DataBMS bmsData;

const DataBMS bms_get_data()   
{
    return bmsData;
}

void bms_manager_init(HardwareSerial& serial){
    bms.Init();
    bms.update();
}

void bms_manager_update(){
    bms.update();
    bmsData.batVolatge = bms.get.packVoltage;
    bmsData.batCurrent = bms.get.packCurrent;
    bmsData.batTemp = bms.get.cellTemperature[0];
    bmsData.batProcent = bms.get.packSOC;
    bmsData.getChargeState = bms.get.chargeFetState;
    bmsData.getDischargeState = bms.get.disChargeFetState;
}

float bms_get_soc(){
    return bms.get.packSOC;
}

float bms_get_bat_voltage(){
    return bms.get.packVoltage;
}

float bms_get_current(){
    return bms.get.packCurrent;
}

float bms_get_temp(){
    return bms.get.cellTemperature[0];
    }


    bool bms_get_charge(){
        return bms.get.chargeFetState;
    }

    bool bms_get_discharge(){
        return bms.get.disChargeFetState;
    }

    void bms_set_discharge(bool state){
        bms.setDischargeMOS(state);
    }
    
    void bms_set_charge(bool state){
        bms.setChargeMOS(state);
    }