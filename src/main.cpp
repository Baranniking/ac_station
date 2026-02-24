
#include <Arduino.h>
#include "ui.h"
#include "bms_manager.h"
#include "TouchInput.h"
#include "logical.h"



void setup() {
 Serial.begin(9600);
 Serial1.begin(9600, SERIAL_8N1, 16, 17);

 bms_manager_init(Serial1);

 displayBegin(); 
 
 touchBegin();

 charger_init();


 
}

void loop() {
    
    if(updateTouch()){
        uiProcessTouch(getLastTouch());
    } 
    logicalUpdateDataBMS();    // 1. Копируем в systemState
    charger_logical();         // 2. Принимаем решения
    updateScreen();            // 3. Рисуем
}
     
     

