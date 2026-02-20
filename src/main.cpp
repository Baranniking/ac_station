
#include <Arduino.h>
#include "ui.h"
#include "bms_manager.h"
#include "TouchInput.h"
#include "logical.h"

TouchPoint p;          // структура


bool touched = false;

float currentPercent = 0;
float targetPercent = 0;


void setup() {
 Serial.begin(9600);
 Serial1.begin(9600, SERIAL_8N1, 16, 17);

 bms_manager_init(Serial1);

 displayBegin(); 
 
 dischargeStatus = bms_get_discharge(); //передаем сотояние bms по розрядке
 delay(100);
 stateChargeAu = bms_get_charge();
 delay(100);
 activSetChargAU(bms_get_charge());

 touchBegin();

 charger_init();
 chargeBegin(&bms);    // передаём ссылку на BMS


 
}

void loop() {
    
    if(updateTouch()){
        uiProcessTouch(getLastTouch());
    } 
    charger_logical();
    updateScreen();

     
     

   

    
    

















    

    if(getCurrentScreen() == SCREEN_CHARGE){
         if (millis() - timeUpdateDataBms >= IntervalUpdate) {
                timeUpdateDataBms = millis();
                bms_get_soc;
                drawChargeValue(
                    bms_get_bat_voltage(),
                    bms_get_current(),
                    bms_get_bat_voltage() * bms_get_current(),
                    bms_get_soc()
                );
    }
    }


}




