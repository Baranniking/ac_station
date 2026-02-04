#ifndef UI_H
#define UI_H

#include <stdint.h>
#include <stdbool.h>
#include <TFT_eSPI.h>
#include <Arduino.h>


void displayBegin();
void drawChargeValue(uint16_t colorBack, uint16_t colorText, uint16_t colorBar, float voltageValue, float currentValue, float powerValue);
void gridStatus(bool gridStat);
void cleanMenu();


#endif