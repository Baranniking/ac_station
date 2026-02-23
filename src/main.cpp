
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
    logicalUpdateDataBMS();    // 2. Копируем в systemState
    charger_logical();         // 3. Принимаем решения
    updateScreen();            // 4. Рисуем
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




