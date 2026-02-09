#ifndef UI_H
#define UI_H

#include <stdint.h>
#include <stdbool.h>
#include <TFT_eSPI.h>
#include <Arduino.h>

enum ScreenState
{
    SCREEN_MAIN,
    SCREEN_CHARGE,
    SCREEN_SETTINGS
};

void displayBegin();
void updateScreen();
ScreenState getCurrentScreen();
void setCurrentScreen(ScreenState newScreen);
void setDischargeStatus(bool newDischargeStatus);
void drawChargeValue(uint16_t colorBack, uint16_t colorText, float voltageValue, float currentValue, float powerValue, float socValue);
void drawMainValue(uint16_t colorText, uint8_t volBat);
void drawChargeMenu(uint16_t colorVoltage, uint16_t colorCurrent, uint16_t colorPower);
void gridStatus(bool gridStat);
void drawMainMenu(uint16_t colorCircle);
void drawSettingsMenu();
void drawBulb(uint8_t x, uint8_t y, bool state);
extern bool dischargeStatus;

#endif