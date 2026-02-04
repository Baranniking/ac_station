
#include <Arduino.h>
#include "ui.h"


    bool step = false;

void setup() {
 displayBegin();
}

void loop() {
if(!step){
    drawChargeValue(TFT_BLACK, TFT_RED, TFT_RED, 14.0, 100.0, 1400.0);
    step = true;
}
}

