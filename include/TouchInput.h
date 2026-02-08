#ifndef TOUCHINPUT_H
#define TOUCHINPUT_H

#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
#include <stdint.h>
#include <stdbool.h>


struct TouchPoint{
    int x;
    int y;
    int z;
};

extern XPT2046_Touchscreen ts;
void touchBegin();
TouchPoint getLastTouch();
bool checkTouch();








#endif
