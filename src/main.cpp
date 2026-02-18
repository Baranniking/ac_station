
#include <Arduino.h>
#include "ui.h"
#include "bms_manager.h"
#include "TouchInput.h"
#include "charger.h"

TouchPoint p;          // структура


bool touched = false;

float currentPercent = 0;
float targetPercent = 0;

uint32_t timeUpdateDataBms = 0;
const uint32_t IntervalUpdate = 1*3000; // 3sec

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

    updateScreen();
    charger_logical();
    

     
     

   

    

    if(getCurrentScreen() == SCREEN_MAIN){
    if (millis() - timeUpdateDataBms >= IntervalUpdate){
        timeUpdateDataBms = millis();
        bms_manager_update();
        targetPercent = bms_get_soc();
        currentPercent += (targetPercent - currentPercent) * 0.1;
        int x = procentToX(currentPercent);
        updateMarker(x);
        drawProcentBat(bms_get_soc());
        drawTempReactor(bms_get_temp());
        //drawMainValue(TFT_GREEN, bms.get.packSOC);
        getStatMoc(bms_get_charge());
        getStatDisMoc(bms_get_discharge());
        drawChargeAuIcon(stateChargeAu);
        Serial.println(bms_get_charge());
        Serial.println(charger_get_state());


    } 
}

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




