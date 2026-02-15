
#include <Arduino.h>
#include "ui.h"
#include <daly-bms-uart.h>
#include "TouchInput.h"
#include "charger.h"


#define BMS_SERIAL Serial1

// объекты
Daly_BMS_UART bms(Serial1);

TouchPoint p;          // структура


bool touched = false;

uint32_t timeUpdateDataBms = 0;
const uint32_t IntervalUpdate = 1*3000; // 3sec

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600, SERIAL_8N1, 16, 17);
 
 bms.Init();
 bms.update();
 displayBegin(); 
 
 dischargeStatus = bms.get.disChargeFetState; // передаем сотояние bms
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
        drawMainValue(TFT_GREEN, bms.get.packSOC);
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




