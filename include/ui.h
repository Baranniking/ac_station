#ifndef UI_H
#define UI_H

#include <stdint.h>
#include <stdbool.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include "TouchInput.h"

enum ScreenState
{
    SCREEN_MAIN,
    SCREEN_CHARGE,
    SCREEN_SETTINGS
};


struct tP{
    int x;
    int y;
    int z;
};


struct UIButton{
    uint16_t x1, y1;
    uint16_t x2, y2;
    uint16_t screen;
    void (*action)();
};



void displayBegin();
void uiProcessTouch(const TouchPoint& point);
void updateScreen();
ScreenState getCurrentScreen();
void setCurrentScreen(ScreenState newScreen);
void setDischargeStatus(bool newDischargeStatus);
void drawChargeValue(float voltageValue, float currentValue, float powerValue, float socValue);
void drawMainValue(uint16_t colorText, uint8_t volBat);
void drawChargeMenu();
void gridStatus(bool gridStat);
void drawMainMenu();
void drawSettingsMenu();
void drawBulb(bool state);
void drawChargeAuIcon(bool stateChargeAu);
void drawSettingsIcon();
void drawChargeManualIcon(bool stateCharge);
void drawBattIcon();
void getStatMoc(bool ChargState);
void getStatDisMoc(bool DisStat);
void drawProcentBat(uint8_t procent);
void drawTempReactor(int tempReactor);
void drawScale();
int procentToX(float procent);
void updateMarker(int newX);

void updateValue();

void enterToChargeMenu();
void enterToMainMenu();
void toggleDischargeMode();
void toggleAuChargeMode();

extern bool stateChargeAu;

#endif