#include "TouchInput.h"
#define CS 33

XPT2046_Touchscreen ts(CS); 
static TouchPoint point;
static unsigned long lastTouchTime = 0;
static const unsigned long debounceDelay = 250;
static unsigned long now = 0;


void touchBegin() {
ts.begin();
ts.setRotation(1);

}

bool checkTouch(){
if(!ts.touched()) return false;
TS_Point p = ts.getPoint();
if(p.z > 100){
    point.x = map(p.x, 3600, 500, 0, 320);
    point.y = map(p.y, 3500, 500, 0, 240);
    point.z = p.z;
    now  = millis();
    if(now - lastTouchTime < debounceDelay) return false;
    lastTouchTime = now;
    return true;
}
return false;
}

TouchPoint getLastTouch(){
      return point;

}

