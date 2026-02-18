
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
 
 dischargeStatus = bms_get_charger(); // передаем сотояние bms
 delay(100);
 stateChargeAu = bms.get.chargeFetState;
 delay(100);
 activSetChargAU(bms.get.chargeFetState);
 touchBegin();

 charger_init();
 chargeBegin(&bms);    // передаём ссылку на BMS


 
}

void loop() {
    updateScreen();
    charger_logical();


    if(checkTouch()) {
    TouchPoint p = getLastTouch();
    Serial.print("X: "); Serial.print(p.x);
    Serial.print(" Y: "); Serial.println(p.y);
    Serial.print(" Z: "); Serial.println(p.z);
    

    if(getCurrentScreen() == SCREEN_CHARGE){
     if(p.x >= 150 && p.x <= 170 && //если было нажатие на кнопку "main"
     p.y >= 220 && p.y <= 250){
        setCurrentScreen(SCREEN_MAIN);
     }
     }
     
     if(getCurrentScreen() == SCREEN_MAIN){
     if(p.x >= 140 && p.x <= 180 && //если было нажатие на кнопку "charge"
     p.y >= 120 && p.y <= 160){
        setCurrentScreen(SCREEN_CHARGE);
<<<<<<< HEAD
     }else if(p.x >= 0 && p.x <= 50 && //если было нажатие на кнопку розряд
     p.y >= 0 && p.y <= 50){
        bmsDischSet = !bmsDischSet;
        bms.setDischargeMOS(bmsDischSet);
        delay (100);
        drawBulb(30, 30, !bms.get.disChargeFetState);

=======
>>>>>>> a2b5eae2878d6c4344bef417622e8a8b9c441fe4
     }
     }

     if(getCurrentScreen() == SCREEN_MAIN){
     if(p.x >= 0 && p.x <= 50 && //если было нажатие на кнопку "discharge"
     p.y >= 0 && p.y <= 50){
        dischargeStatus = !dischargeStatus;
        bms.setDischargeMOS(dischargeStatus);
        drawBulb(dischargeStatus);
     }
     }

     if(getCurrentScreen() == SCREEN_MAIN){
     if(p.x >= 280 && p.x <= 320 && //если было нажатие на кнопку AU CHARGE
        p.y >= 0 && p.y <= 50){
            stateChargeAu = !stateChargeAu;
        }
        if(stateChargeAu){
            charger_set_state(CHARGER_AUTO);
            drawChargeAuIcon(stateChargeAu);
        }else{
            charger_set_state(CHARGER_OFF);
           drawChargeAuIcon(stateChargeAu);
        }
}
    }

    if(getCurrentScreen() == SCREEN_MAIN){
    if (millis() - timeUpdateDataBms >= IntervalUpdate){
        timeUpdateDataBms = millis();
        bms.update();
        targetPercent = bms.get.packSOC;
        currentPercent += (targetPercent - currentPercent) * 0.1;
        int x = procentToX(currentPercent);
        updateMarker(x);
        drawProcentBat(bms.get.packSOC);
        drawTempReactor(bms.get.cellTemperature[0]);
        //drawMainValue(TFT_GREEN, bms.get.packSOC);
        getStatMoc(bms.get.chargeFetState);
        getStatDisMoc(bms.get.disChargeFetState);
        drawChargeAuIcon(stateChargeAu);
        Serial.println(bms.get.chargeFetState);
        Serial.println(charger_get_state());


    } 
}

    if(getCurrentScreen() == SCREEN_CHARGE){
         if (millis() - timeUpdateDataBms >= IntervalUpdate) {
                timeUpdateDataBms = millis();
                bms.update();
                drawChargeValue(
                    bms.get.packVoltage,
                    bms.get.packCurrent,
                    bms.get.packVoltage * bms.get.packCurrent,
                    bms.get.packSOC
                );
    }
    }


}




