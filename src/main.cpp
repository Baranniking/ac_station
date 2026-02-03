
#include <Arduino.h>
#include "ui.h"


    bool step = false;

void setup() {
 displayBegin();
}

void loop() {
if(!step){
    drawVoltageValue(TFT_WHITE, TFT_BLACK, TFT_RED, 14.0, 15.0, 200.0);
    step = true;
}
}

