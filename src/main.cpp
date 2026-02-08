
#include <Arduino.h>
#include "ui.h"
#include <daly-bms-uart.h>
#include "TouchInput.h"


#define BMS_SERIAL Serial1

// объекты
Daly_BMS_UART bms(Serial1);


bool bmsDischSet = true;

uint32_t timeUpdateDataBms = 0;
const uint32_t IntervalUpdate = 1*1000; // 1sec

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600, SERIAL_8N1, 16, 17);
 
 bms.Init();
 bms.update();
 displayBegin(); 
 touchBegin();
 
}

void loop() {
    updateScreen();
    
    if (checkTouch()) {
    TouchPoint p = getLastTouch();
    Serial.print("X: "); Serial.print(p.x);
    Serial.print(" Y: "); Serial.println(p.y);
    Serial.print(" Z: "); Serial.println(p.z);

    if(p.x >= 150 && p.x <= 170 && //если было нажатие на кнопку "сеть"
     p.y >= 220 && p.y <= 250){
        setCurrentScreen(SCREEN_MAIN);
     }else if(p.x >= 140 && p.x <= 180 && //если было нажатие на кнопку "сеть"
     p.y >= 120 && p.y <= 160){
        setCurrentScreen(SCREEN_CHARGE);
     }else if(p.x >= 0 && p.x <= 50 && //если было нажатие на кнопку розряд
     p.y >= 0 && p.y <= 50){
        bmsDischSet = !bmsDischSet;
        bms.setDischargeMOS(!bmsDischSet);

     }
}

if(getCurrentScreen() == SCREEN_MAIN){
    if (millis() - timeUpdateDataBms >= 2000){
        timeUpdateDataBms = millis();
        bms.update();
        drawMainValue(TFT_GREEN, bms.get.packSOC);

    } 
}

    if(getCurrentScreen() == SCREEN_CHARGE){
         if (millis() - timeUpdateDataBms >= 2000) {
                timeUpdateDataBms = millis();
            bms.update();
                drawChargeValue(
                    TFT_BLACK,
                    TFT_GREEN,
                    bms.get.packVoltage,
                    bms.get.packCurrent,
                    bms.get.packVoltage * bms.get.packCurrent,
                    bms.get.packSOC
                );
    }
    }
}





